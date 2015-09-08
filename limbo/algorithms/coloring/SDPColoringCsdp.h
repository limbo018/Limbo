/*************************************************************************
    > File Name: SDPColoringCsdp.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 01 Sep 2015 12:01:32 PM CDT
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_SDPCOLORINGCSDP
#define LIMBO_ALGORITHMS_COLORING_SDPCOLORINGCSDP

#include <limbo/string/String.h>
#include <limbo/algorithms/coloring/Coloring.h>

// must define NOSHORTS to forbid the usage of unsigned shorts in Csdp 
#define NOSHORTS
// as the original csdp easy_sdp api is not very flexible to printlevel
// I made small modification to support that 
#include <limbo/solvers/api/CsdpEasySdpApi.h>

//////////////////////////////////////////////////////////////////////////////////
/// SDP formulation from Bei Yu's TCAD 2015 paper 
/// min. C X 
/// s.t. xii = 1, for all i in V
///      xij >= -0.5, for all (i, j) in E 
///      X >= 0 (PSD)
/// Note that Csdp only solves equality problem for constraints 
/// so it is necessary to introduce slack variables for each conflict edge.
/// The total number of variables are N = (vertex number + conflict edge number).
/// The variable matrix has dimension NxN. 
//////////////////////////////////////////////////////////////////////////////////

namespace limbo { namespace algorithms { namespace coloring {

template <typename GraphType>
class SDPColoringCsdp : public Coloring<GraphType>
{
	public:
		typedef Coloring<GraphType> base_type;
		using typename base_type::graph_type;
		using typename base_type::graph_vertex_type;
		using typename base_type::graph_edge_type;
		using typename base_type::vertex_iterator_type;
		using typename base_type::edge_iterator_type;
		using typename base_type::ColorNumType;
        typedef typename base_type::EdgeHashType edge_hash_type;
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::type edge_weight_map_type;
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::const_type const_edge_weight_map_type;

		/// constructor
		SDPColoringCsdp(graph_type const& g) 
			: base_type(g)
		{}
		/// destructor
		virtual ~SDPColoringCsdp() {}

        /// for debug 
        /// write sdp solution to file 
        void write_sdp_sol(std::string const& filename, struct blockmatrix const& X) const; 
        /// print data in blockrec 
        void print_blockrec(const char* label, blockrec const& block) const; 
	protected:
		/// \return objective value 
		virtual double coloring();
        /// helper functions 
        /// construct blockrec in C for objective 
        void construct_objectve_blockrec(blockmatrix& C, int32_t blocknum, int32_t blocksize, blockcat blockcategory) const; 
        /// construct sparseblock for constraint 
        struct sparseblock* construct_constraint_sparseblock(int32_t blocknum, int32_t blocksize, int32_t constraintnum, int32_t entrynum) const; 
        /// set entry for sparseblock 
        void set_sparseblock_entry(struct sparseblock& block, int32_t entryid, int32_t i, int32_t j, double value) const; 
        /// round sdp solution 
        void round_sol(struct blockmatrix const& X);
};

template <typename GraphType>
double SDPColoringCsdp<GraphType>::coloring()
{
    // Since Csdp is written in C, the api here is also in C 
    // Please refer to the documation of Csdp for different notations 
    // basically, X is primal variables, C, b, constraints and pobj are all for primal 
    // y, Z, and dobj are for dual problem 
    //
    // Csdp has very complex storage structure for matrix 
    // I still do not have a full understanding about the block concept, especially blocks.blocksize 
    // with some reverse engineering, for the coloring problem here, matrices in C, b, and constraints mainly consists of 2 blocks 
    // the first block is for vertex variables, and the second block is for slack variables introduced to resolve '>=' operators in the constraints

    // The problem and solution data.
    struct blockmatrix C; // objective matrix 
    double *b; // right hand side of constraints
    struct constraintmatrix *constraints; // constraint matrices
    // Storage for the initial and final solutions.
    struct blockmatrix X,Z;
    double *y;
    double pobj,dobj;

    // iterators used to traverse through the graph 
    vertex_iterator_type vi, vie; 
    edge_iterator_type ei, eie; 
    // compute total number of vertices and edges 
    uint32_t num_vertices = boost::num_vertices(this->m_graph);
    uint32_t num_edges = boost::num_edges(this->m_graph);
    // compute total number of conflict edges and stitch edges 
    uint32_t num_conflict_edges = 0;
    uint32_t num_stitch_edges = 0;
    for (boost::tie(ei, eie) = boost::edges(this->m_graph); ei != eie; ++ei)
    {
        if (this->edge_weight(*ei) >= 0) // conflict edge 
            num_conflict_edges += 1;
        else // stitch edge 
            num_stitch_edges += 1;
    }
    assert_msg(num_edges > 0 && num_conflict_edges > 0, "no edges or conflict edges found, no need to solve SDP");
    // compute total number of variables and constraints
    uint32_t num_variables = num_vertices+num_conflict_edges;
    uint32_t num_constraints = num_conflict_edges+num_vertices;

    // setup blockmatrix C 
    C.nblocks = 2;
    C.blocks = (struct blockrec *)malloc((C.nblocks+1)*sizeof(struct blockrec));
    assert_msg(C.blocks, "Couldn't allocate storage for C");
    // C.blocks[0] is not used according to the example of Csdp
    // block 1 for vertex variables 
    construct_objectve_blockrec(C, 1, num_vertices, MATRIX);
    for (boost::tie(ei, eie) = boost::edges(this->m_graph); ei != eie; ++ei)
    {
        graph_vertex_type s = boost::source(*ei, this->m_graph);
        graph_vertex_type t = boost::target(*ei, this->m_graph);
        // 1 for conflict edge, -alpha for stitch edge 
        // add unary negative operator, because Csdp solves maximization problem 
        // but we are solving minimization problem 
        double alpha = (this->edge_weight(*ei) >= 0)? -1 : this->stitch_weight();
        // variable starts from 1 instead of 0 in Csdp
        s += 1; t += 1;
        int32_t idx1 = ijtok(s,t,C.blocks[1].blocksize);
        int32_t idx2 = ijtok(t,s,C.blocks[1].blocksize);
        C.blocks[1].data.mat[idx1] = alpha; 
        C.blocks[1].data.mat[idx2] = alpha;
    }
    // block 2 for slack variables 
    // this block is all 0s, so we use diagonal format to represent  
    construct_objectve_blockrec(C, 2, num_conflict_edges, DIAG);
#ifdef DEBUG_SDPCOLORING
    print_blockrec("C.blocks[1].data.mat", C.blocks[1]);
    print_blockrec("C.blocks[2].data.vec", C.blocks[2]);
#endif

    // setup right hand side of constraints b
    // the order is first for conflict edges and then for vertices  
    // the order matters for constraint matrices 
    b = (double *)malloc((num_constraints+1)*sizeof(double));
    assert_msg(b, "Failed to allocate storage for right hand side of constraints b");
    double beta = -2.0/(this->color_num()-1.0); // right hand side of constraints for conflict edges 
    for (uint32_t i = 1, ie = num_constraints+1; i != ie; ++i)
    {
        if (i <= num_conflict_edges) // slack for each conflict edge, xij >= -0.5
            b[i] = beta;
        else // slack for each vertex, xii = 1
            b[i] = 1;
    }

    // setup constraint matrix constraints
    // the order should be the same as right hand side b 
    constraints=(struct constraintmatrix *)malloc((num_constraints+1)*sizeof(struct constraintmatrix));
    assert_msg(constraints, "Failed to allocate storage for constraints");
    // for conflict edges, xij 
    uint32_t cnt = 1;
    for (boost::tie(ei, eie) = boost::edges(this->m_graph); ei != eie; ++ei)
    {
        if (this->edge_weight(*ei) >= 0) // conflict edge 
        {
            graph_vertex_type s = boost::source(*ei, this->m_graph);
            graph_vertex_type t = boost::target(*ei, this->m_graph);
            if (s > t) // due to symmetry, only need to create constraint matrices for upper-matrix 
                std::swap(s, t);
            // variable starts from 1 instead of 0 in Csdp
            s += 1; t += 1;
            struct constraintmatrix& constr = constraints[cnt];
            // Terminate the linked list with a NULL pointer.
            constr.blocks = NULL;
            // inverse order to initialize blocks, because linked list will reverse the order 
            // first set block 2 for diagonal values and then block 1 for upper-matrix values  
            for (uint32_t i = 2; i != 0; --i)
            {
                struct sparseblock* blockptr;
                if (i == 1) // block 1, vertex variables  
                {
                    blockptr = construct_constraint_sparseblock(i, num_vertices, cnt, 1);
                    set_sparseblock_entry(*blockptr, 1, s, t, 1);
                }
                else // block 2, slack variables 
                {
                    blockptr = construct_constraint_sparseblock(i, num_conflict_edges, cnt, 1);
                    set_sparseblock_entry(*blockptr, 1, cnt, cnt, -1);
                }
                // insert block to linked list 
                blockptr->next = constr.blocks;
                constr.blocks = blockptr;
            }
            ++cnt;
        }
    }
    // for vertices, xii 
    for (boost::tie(vi, vie) = boost::vertices(this->m_graph); vi != vie; ++vi)
    {
        graph_vertex_type v = *vi;
        v += 1;
        struct constraintmatrix& constr = constraints[cnt];
        // Terminate the linked list with a NULL pointer.
        constr.blocks = NULL;
        struct sparseblock* blockptr = construct_constraint_sparseblock(1, num_vertices, cnt, 1);
        set_sparseblock_entry(*blockptr, 1, v, v, 1);
        // insert block to linked list 
        blockptr->next = constr.blocks;
        constr.blocks = blockptr;
        ++cnt;
    }

#ifdef DEBUG_SDPCOLORING
    write_prob((char*)"problem.sdpa", num_variables, num_constraints, C, b, constraints);
#endif

    // after all configuration ready 
    // start solving sdp 
    // set initial solution 
    initsoln(num_variables, num_constraints, C, b, constraints, &X, &y, &Z);
    // use default params 
    // only set printlevel to zero 
    struct paramstruc params; 
    int printlevel;
    initparams(&params, &printlevel);
#ifndef DEBUG_SDPCOLORING
    printlevel = 0;
#endif
    // A return code for the call to easy_sdp().
    // solve sdp 
    // objective value is (dobj+pobj)/2
    //int ret = easy_sdp(num_variables, num_constraints, C, b, constraints, 0.0, &X, &y, &Z, &pobj, &dobj);
    int ret = limbo::solvers::easy_sdp_ext<int>(num_variables, num_constraints, C, b, constraints, 0.0, &X, &y, &Z, &pobj, &dobj, params, printlevel);
    assert_msg(ret == 0, "SDP failed");

    // round result to get colors 
    round_sol(X);

    // Free storage allocated for the problem and return.
    free_prob(num_variables, num_constraints, C, b, constraints, X, y, Z);

    // return objective value 
    return (dobj+pobj)/2;
}

template <typename GraphType>
void SDPColoringCsdp<GraphType>::construct_objectve_blockrec(blockmatrix& C, int32_t blocknum, int32_t blocksize, blockcat blockcategory) const 
{
    struct blockrec& cblock = C.blocks[blocknum];
    cblock.blocksize = blocksize;
    cblock.blockcategory = blockcategory;
    if (blockcategory == MATRIX)
    {
        cblock.data.mat = (double *)malloc(blocksize*blocksize*sizeof(double));
        assert_msg(cblock.data.mat, "Couldn't allocate storage for cblock.data.mat");
        // initialize to all 0s
        std::fill(cblock.data.mat, cblock.data.mat+blocksize*blocksize, 0); 
    }
    else if (blockcategory == DIAG)
    {
        cblock.data.vec = (double *)malloc((blocksize+1)*sizeof(double));
        assert_msg(cblock.data.vec, "Couldn't allocate storage for cblock.data.vec");
        // initialize to all 0s
        std::fill(cblock.data.vec, cblock.data.vec+blocksize+1, 0); 
    }
}

template <typename GraphType>
struct sparseblock* SDPColoringCsdp<GraphType>::construct_constraint_sparseblock(int32_t blocknum, int32_t blocksize, int32_t constraintnum, int32_t entrynum) const 
{
    struct sparseblock* blockptr = (struct sparseblock *)malloc(sizeof(struct sparseblock));
    assert_msg(blockptr, "Allocation of constraint block failed for blockptr");
    blockptr->blocknum = blocknum;
    blockptr->blocksize = blocksize;
    blockptr->constraintnum = constraintnum;
    blockptr->next = NULL;
    blockptr->nextbyblock = NULL;
    blockptr->entries = (double *) malloc((entrynum+1)*sizeof(double));
    assert_msg(blockptr->entries, "Allocation of constraint block failed for blockptr->entries");
    blockptr->iindices = (int *) malloc((entrynum+1)*sizeof(int));
    assert_msg(blockptr->iindices, "Allocation of constraint block failed for blockptr->iindices");
    blockptr->jindices = (int *) malloc((entrynum+1)*sizeof(int));
    assert_msg(blockptr->jindices, "Allocation of constraint block failed for blockptr->jindices");
    blockptr->numentries = entrynum;

    return blockptr;
}

template <typename GraphType>
void SDPColoringCsdp<GraphType>::set_sparseblock_entry(struct sparseblock& block, int32_t entryid, int32_t i, int32_t j, double value) const 
{
    block.iindices[entryid] = i;
    block.jindices[entryid] = j;
    block.entries[entryid] = value;
}

template <typename GraphType>
void SDPColoringCsdp<GraphType>::round_sol(struct blockmatrix const& X)
{
#ifdef DEBUG_SDPCOLORING
    write_sdp_sol("problem.sol", X);
#endif
}

template <typename GraphType>
void SDPColoringCsdp<GraphType>::write_sdp_sol(std::string const& filename, struct blockmatrix const& X) const 
{
    // compute dimensions of matrix 
    uint32_t matrix_size = 0;
    for (int32_t blk = 1; blk <= X.nblocks; ++blk)
        matrix_size += X.blocks[blk].blocksize;

    // collect data from X and store to mSol 
    std::vector<std::vector<double> > mSol (matrix_size, std::vector<double>(matrix_size, 0.0));
    // as i and j starts from 1, set index_offset to -1 
    int32_t index_offset = 0; 
    for (int32_t blk = 1; blk <= X.nblocks; ++blk)
    {
        switch (X.blocks[blk].blockcategory)
        {
            case DIAG:
                for (int32_t i = 1; i <= X.blocks[blk].blocksize; ++i)
                {
                    double ent = X.blocks[blk].data.vec[i];
                    if (ent != 0.0)
                        mSol[index_offset+i-1][index_offset+i-1] = ent;
                };
                break;
            case MATRIX:
                for (int32_t i = 1; i <= X.blocks[blk].blocksize; ++i)
                    for (int32_t j = i; j <= X.blocks[blk].blocksize; ++j)
                    {
                        double ent = X.blocks[blk].data.mat[ijtok(i, j, X.blocks[blk].blocksize)];
                        if (ent != 0.0)
                            mSol[index_offset+i-1][index_offset+j-1] = ent;
                    };
                break;
            case PACKEDMATRIX:
            default: assert_msg(0, "Invalid Block Type");
        }
        index_offset += X.blocks[blk].blocksize; 
    }

    // write to file 
    std::ofstream out (filename.c_str());
    assert_msg(out.good(), "failed to open file " << filename << " for write");
    for (std::vector<std::vector<double> >::const_iterator it1 = mSol.begin(), it1e = mSol.end(); it1 != it1e; ++it1)
    {
        const char* prefix = "";
        for (std::vector<double>::const_iterator it2 = it1->begin(), it2e = it1->end(); it2 != it2e; ++it2)
        {
            out << prefix << *it2;
            prefix = ",";
        }
        out << std::endl;
    }
    out.close();
}

template <typename GraphType>
void SDPColoringCsdp<GraphType>::print_blockrec(const char* label, blockrec const& block) const 
{
    printf("%s", label);
    if (block.blockcategory == MATRIX)
    {
        printf("[M]: "); // show it is a matrix 
        for (int32_t i = 0, ie = block.blocksize*block.blocksize; i != ie; ++i)
            printf("%g ", block.data.mat[i]);
    }
    else if (block.blockcategory == DIAG)
    {
        printf("[V]: "); // show it is a vector 
        for (int32_t i = 0; i != block.blocksize; ++i)
            printf("%g ", block.data.vec[i+1]);
    }
    printf("\n");
}

}}} // namespace limbo // namespace algorithms // namespace coloring

#endif
