/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

/*#include "expression.h"*/

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "3.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define api.prefix {BookshelfParser}

/* set the parser's class identifier */
%define api.parser.class {Parser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%define parse.error verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    int  			integerVal;
    double 			doubleVal;
    char            charVal;
    double          numberVal;
    std::string*		stringVal;
	std::string*		quoteVal;
	std::string*		binaryVal;

	class IntegerArray* integerArrayVal;
	class StringArray* stringArrayVal;
}

%token			END	     0	"end of file"
%token			EOL		"end of line" 
%token <integerVal> 	INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"
%token <quoteVal> 	QUOTE		"quoted chars"
%token <binaryVal> 	BINARY		"binary numbers"
%token			KWD_NUMNETS		"NumNets"
%token          KWD_NUMPINS     "NumPins"
%token          KWD_NUMNODES    "NumNodes"
%token          KWD_NUMTERMINALS "NumTerminals"
%token          KWD_NUMNONRECTANGULARNODES "NumNonRectangularNodes"
%token          KWD_NUMROWS     "NumRows"
%token          KWD_COREROW     "CoreRow"
%token          KWD_HORIZONTAL  "Horizontal"
%token          KWD_VERTICAL    "Vertical"
%token          KWD_COORDINATE  "Coordinate"
%token          KWD_HEIGHT      "Height"
%token          KWD_SITEWIDTH   "Sitewidth"
%token          KWD_SITESPACING "Sitespacing"
%token          KWD_SITEORIENT  "Siteorient"
%token          KWD_SITESYMMETRY "Sitesymmetry"
%token          KWD_SUBROWORIGIN "SubrowOrigin"
%token          KWD_NUMSITES    "NumSites"
%token          KWD_END         "End"
%token          KWD_TERMINAL    "terminal"
%token          KWD_TERMINAL_NI "terminal_NI"
%token          KWD_UCLA        "UCLA"
%token          KWD_NETDEGREE   "NetDegree"
%token          KWD_SCL         "scl"
%token          KWD_NODES       "nodes"
%token          KWD_NETS        "nets"
%token          KWD_PL          "pl"
%token          KWD_WTS         "wts"
%token          KWD_SHAPES      "shapes"
%token          KWD_ROUTE       "route"
%token          KWD_AUX         "aux"
%token          KWD_FIXED       "FIXED"
%token          KWD_FIXED_NI    "FIXED_NI"
%token          KWD_PLACED      "PLACED"
%token          KWD_UNPLACED    "UNPLACED"
%token          KWD_O           "O"
%token          KWD_I           "I"
%token          KWD_B           "B"
%token          KWD_N           "N"
%token          KWD_S           "S"
%token          KWD_W           "W"
%token          KWD_E           "E"
%token          KWD_FN          "FN"
%token          KWD_FS          "FS"
%token          KWD_FW          "FW"
%token          KWD_FE          "FE"
%token			KWD_GRID		"Grid"
%token			KWD_VERTICALCAPACITY		"VerticalCapacity"
%token			KWD_HORIZONTALCAPACITY		"HorizontalCapacity"
%token			KWD_MINWIREWIDTH		    "MinWireWidth"
%token			KWD_MINWIRESPACING		    "MinWireSpacing"
%token			KWD_VIASPACING		        "ViaSpacing"
%token			KWD_GRIDORIGIN		        "GridOrigin"
%token			KWD_TILESIZE		        "TileSize"
%token			KWD_BLOCKAGE_POROSITY		"BlockagePorosity"
%token			KWD_NUMNITERMINALS		    "NumNiTerminals"
%token			KWD_NUMBLOCKAGENODES		"NumBlockageNodes"

%type <integerArrayVal> integer_array 
%type <stringArrayVal> string_array 
%type <numberVal>  NUMBER      
%type <charVal> nets_pin_direct
%type <stringVal> pl_status
%type <stringVal> orient

/*
%type <integerVal>	block_other block_row block_comp block_pin block_net 
%type <integerVal>	expression 
*/

%destructor { delete $$; } STRING QUOTE BINARY 
%destructor { delete $$; } integer_array string_array  
%destructor { delete $$; } orient pl_status
/*
%destructor { delete $$; } constant variable
%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr
*/

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "BookshelfDriver.h"
#include "BookshelfScanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

integer_array : INTEGER {
				$$ = new IntegerArray(1, $1);
			  }
			  | integer_array INTEGER {
				$1->push_back($2);
				$$ = $1;
			  }
              ;
string_array : STRING {
				$$ = new StringArray(1, *$1);
                delete $1;
			  }
			  | string_array STRING {
				$1->push_back(*$2);
                delete $2;
				$$ = $1;
			  }
              ;
NUMBER : INTEGER {$$ = $1;}
       | DOUBLE {$$ = $1;}
       ;

/***** .nodes file *****/
nodes_header : KWD_UCLA KWD_NODES DOUBLE
             | KWD_NODES DOUBLE
             | nodes_header EOL /* swallow up EOL by recursion  */
             ; 

nodes_number : KWD_NUMNODES ':' INTEGER EOL 
             KWD_NUMTERMINALS ':' INTEGER {
              driver.numNodeTerminalsCbk($3, $7);
             }
             | KWD_NUMNODES ':' INTEGER 
             KWD_NUMTERMINALS ':' INTEGER {
              driver.numNodeTerminalsCbk($3, $6);
             }
             | KWD_NUMTERMINALS ':' INTEGER EOL 
             KWD_NUMNODES ':' INTEGER {
              driver.numNodeTerminalsCbk($3, $7);
             }
             | KWD_NUMTERMINALS ':' INTEGER 
             KWD_NUMNODES ':' INTEGER {
              driver.numNodeTerminalsCbk($3, $6);
             }
              ;

nodes_numbers : nodes_number 
              | nodes_numbers nodes_number
              | nodes_numbers EOL
              ;

nodes_node_entry : STRING INTEGER INTEGER KWD_TERMINAL EOL {
                 driver.terminalEntryCbk(*$1, $2, $3);
                     delete $1;
                     } 
                     | STRING INTEGER INTEGER KWD_TERMINAL_NI EOL {
                     driver.terminalNIEntryCbk(*$1, $2, $3);
                     delete $1;
                     } 
                     | STRING INTEGER INTEGER STRING EOL {
                 driver.nodeEntryCbk(*$1, $2, $3, *$4);
                 delete $1;
                 delete $4;
                 }
                 | STRING INTEGER INTEGER EOL {
                 driver.nodeEntryCbk(*$1, $2, $3);
                 delete $1;
                 }
                 ;

nodes_block_node_entries : nodes_node_entry 
                         | nodes_block_node_entries nodes_node_entry
                         | nodes_block_node_entries EOL 
                         ; 

/* .nodes top */
bookshelf_nodes : nodes_header 
                nodes_numbers 
                nodes_block_node_entries
                ;


/***** .nets file *****/
nets_header : KWD_UCLA KWD_NETS DOUBLE 
            | nets_header EOL
            ; 

nets_number : KWD_NUMNETS ':' INTEGER {driver.numNetCbk($3);}
            | KWD_NUMPINS ':' INTEGER {driver.numPinCbk($3);}
            ;

nets_numbers : nets_number 
             | nets_numbers nets_number
             | nets_numbers EOL
            ;

nets_pin_direct : KWD_O {$$='O';} 
                | KWD_I {$$='I';}
                | KWD_B {$$='B';}
                ;

nets_pin_entry : STRING nets_pin_direct ':' NUMBER NUMBER ':' NUMBER NUMBER STRING EOL {
               driver.netPinEntryCbk(*$1, 'O', $4, $5, $7, $8, *$9);
               delete $1;
               delete $9;
               }
               | STRING nets_pin_direct ':' NUMBER NUMBER ':' NUMBER NUMBER EOL {
               driver.netPinEntryCbk(*$1, $2, $4, $5, $7, $8);
               delete $1;
               }
               | STRING nets_pin_direct ':' NUMBER NUMBER EOL{
               driver.netPinEntryCbk(*$1, $2, $4, $5);
               delete $1;
               }
               ;

nets_pin_entries : nets_pin_entry 
                 | nets_pin_entries nets_pin_entry
                 | nets_pin_entries EOL
                 ;

nets_name : KWD_NETDEGREE ':' INTEGER STRING  {driver.netNameAndDegreeCbk(*$4, $3); delete $4;}
          | nets_name EOL
          ;

nets_entry : nets_name
           nets_pin_entries {driver.netEntryCbk();}
           ;

nets_entries : nets_entry
             | nets_entries nets_entry
             ;

/* .nets top */
bookshelf_nets : nets_header
               nets_numbers 
               nets_entries
               ; 

/***** .pl file *****/
pl_header : KWD_UCLA KWD_PL DOUBLE 
          | KWD_PL DOUBLE 
          | pl_header EOL
            ;

orient : KWD_N {$$ = new std::string ("N");}
          | KWD_S {$$ = new std::string ("S");}
          | KWD_W {$$ = new std::string ("W");}
          | KWD_E {$$ = new std::string ("E");}
          | KWD_FN {$$ = new std::string ("FN");}
          | KWD_FS {$$ = new std::string ("FS");}
          | KWD_FW {$$ = new std::string ("FW");}
          | KWD_FE {$$ = new std::string ("FE");}
          ;

pl_status : KWD_FIXED {$$ = new std::string("FIXED");}
          | KWD_FIXED_NI {$$ = new std::string("FIXED_NI");}
          | KWD_PLACED {$$ = new std::string("PLACED");}
          | KWD_UNPLACED {$$ = new std::string("UNPLACED");}
          ;

pl_node_entry : STRING NUMBER NUMBER ':' orient pl_status {
              driver.plNodeEntryCbk(*$1, $2, $3, *$5, *$6);
              delete $1;
              delete $5;
              delete $6;
              }
              | STRING NUMBER NUMBER ':' orient {
              driver.plNodeEntryCbk(*$1, $2, $3, *$5);
              delete $1;
              delete $5;
              }
              ;

pl_node_entries : pl_node_entry
                | pl_node_entries pl_node_entry
                | pl_node_entries EOL
                ;

/* .pl top */
bookshelf_pl : pl_header
             pl_node_entries
             ;


/***** .scl file *****/
scl_header : KWD_UCLA KWD_SCL DOUBLE 
           | KWD_SCL DOUBLE 
           | scl_header EOL
           ;

scl_numbers : KWD_NUMROWS ':' INTEGER {driver.sclNumRows($3);}
            | scl_numbers EOL
            ;

scl_corerow_start : KWD_COREROW KWD_HORIZONTAL {
                  driver.sclCoreRowStart("HORIZONTAL");
                  }
                  | KWD_COREROW KWD_VERTICAL {
                  driver.sclCoreRowStart("VERTICAL");
                  }
                  | scl_corerow_start EOL
                  ;

scl_corerow_property : KWD_COORDINATE ':' INTEGER {driver.sclCoreRowCoordinate($3);}
                  | KWD_HEIGHT ':' INTEGER {driver.sclCoreRowHeight($3);}
                  | KWD_SITEWIDTH ':' INTEGER {driver.sclCoreRowSitewidth($3);}
                  | KWD_SITESPACING ':' INTEGER {driver.sclCoreRowSitespacing($3);}
                  | KWD_SITEORIENT ':' orient {driver.sclCoreRowSiteorient(*$3); delete $3;}
                  | KWD_SITEORIENT ':' INTEGER {driver.sclCoreRowSiteorient($3);}
                  | KWD_SITESYMMETRY ':' STRING {driver.sclCoreRowSitesymmetry(*$3); delete $3;}
                  | KWD_SITESYMMETRY ':' INTEGER {driver.sclCoreRowSitesymmetry($3);}
                  | KWD_SUBROWORIGIN ':' INTEGER {driver.sclCoreRowSubRowOrigin($3);}
                  | KWD_NUMSITES ':' INTEGER {driver.sclCoreRowNumSites($3);}
                  ;

scl_corerow_properties : scl_corerow_property
                       | scl_corerow_properties scl_corerow_property
                       | scl_corerow_properties EOL 
                       ;

scl_corerow_entry : scl_corerow_start
                  scl_corerow_properties
                  KWD_END {
                  driver.sclCoreRowEnd();
                  }
                  | scl_corerow_entry EOL
                  ;

scl_corerow_entries : scl_corerow_entry
                    | scl_corerow_entries scl_corerow_entry
                    ;

/* .scl top */
bookshelf_scl : scl_header
              scl_numbers
              scl_corerow_entries
              ;

/***** .wts file (not implemented) *****/
wts_header : KWD_UCLA KWD_WTS DOUBLE
           | KWD_WTS DOUBLE 
           | wts_header EOL
           ;

wts_entry : STRING NUMBER {
          driver.wtsNetWeightEntry(*$1, $2);
          delete $1;
          }
          | wts_entry EOL
          ;

wts_entries : wts_entry 
            | wts_entries wts_entry 
            ;

/* .wts top */
bookshelf_wts : wts_header
              wts_entries
              | wts_header
              ;

/***** .shapes file *****/
shapes_header : KWD_UCLA KWD_SHAPES DOUBLE
             | KWD_SHAPES DOUBLE 
             | shapes_header EOL /* swallow up EOL by recursion  */
             ; 

shapes_number : KWD_NUMNONRECTANGULARNODES ':' INTEGER {
              driver.shapesNumNonRectangularNodesCbk($3);
             }
             | shapes_number EOL
              ;

shapes_one_line_entry : STRING NUMBER NUMBER NUMBER NUMBER {
             driver.shapesEntryCbk(*$1, $2, $3, $4, $5);
             delete $1; 
             }
             | STRING ':' INTEGER {
                 driver.shapesNodeNameCbk(*$1, $3);
             }
             | shapes_one_line_entry EOL
             ;

shapes_node_entries : shapes_one_line_entry
                    | shapes_node_entries shapes_one_line_entry
                    ;

/* .shapes top */
bookshelf_shapes : shapes_header
               shapes_number 
               shapes_node_entries {
               driver.shapesEndCbk();
               }
               | shapes_header
               ; 

/***** .route file *****/
route_header : KWD_UCLA KWD_ROUTE DOUBLE
             | KWD_ROUTE DOUBLE 
             | route_header EOL /* swallow up EOL by recursion  */
             ; 

grid_entry : KWD_GRID ':' INTEGER INTEGER INTEGER {
           driver.routeGridCbk($3, $4, $5); 
           }
           | grid_entry EOL 
           ;

vertical_capacity_entry : KWD_VERTICALCAPACITY ':' integer_array {
                        driver.routeVerticalCapacityCbk(*$3); 
                        delete $3;
                        }
                        | vertical_capacity_entry EOL 
                        ;

horizontal_capacity_entry : KWD_HORIZONTALCAPACITY ':' integer_array {
                          driver.routeHorizontalCapacityCbk(*$3); 
                          delete $3;
                          }
                          | horizontal_capacity_entry EOL 
                          ;

min_wire_width_entry : KWD_MINWIREWIDTH ':' integer_array {
                     driver.routeMinWireWidthCbk(*$3);
                     delete $3;
                     }
                     | min_wire_width_entry EOL 
                     ;

min_wire_spacing_entry : KWD_MINWIRESPACING ':' integer_array {
                     driver.routeMinWireSpacingCbk(*$3);
                     delete $3;
                     }
                     | min_wire_spacing_entry EOL 
                     ;

via_spacing_entry : KWD_VIASPACING ':' integer_array {
                  driver.routeViaSpacingCbk(*$3);
                  delete $3;
                  }
                  | via_spacing_entry EOL 
                  ;

grid_origin_entry : KWD_GRIDORIGIN ':' NUMBER NUMBER {
                  driver.routeGridOriginCbk($3, $4);
                  }
                  | grid_origin_entry EOL 
                  ;

tile_size_entry : KWD_TILESIZE ':' NUMBER NUMBER {
                driver.routeTileSizeCbk($3, $4);
                }
                | tile_size_entry EOL 
                ;

blockage_porosity_entry : KWD_BLOCKAGE_POROSITY ':' INTEGER {
                        driver.routeBlockagePorosityCbk($3);
                        }
                        | blockage_porosity_entry EOL 
                        ;

num_ni_terminals_entry : KWD_NUMNITERMINALS ':' INTEGER {
                      driver.routeNumNiTerminalsCbk($3);
                      }
                      | num_ni_terminals_entry EOL 
                      ;

pin_layer_entry : STRING INTEGER {
                driver.routePinLayerCbk(*$1, $2);
                delete $1;
                }
                | STRING STRING {
                driver.routePinLayerCbk(*$1, *$2);
                delete $1;
                delete $2;
                }
                | pin_layer_entry EOL 
                ;

pin_layer_entries : pin_layer_entry
                  | pin_layer_entries pin_layer_entry
                  ;

pin_layer_block : num_ni_terminals_entry pin_layer_entries
                ;

num_blockage_nodes_entry : KWD_NUMBLOCKAGENODES ':' INTEGER {
                         driver.routeNumBlockageNodes($3);
                         }
                         | num_blockage_nodes_entry EOL 
                         ;

blockage_node_layer_entry : STRING INTEGER integer_array {
                          driver.routeBlockageNodeLayerCbk(*$1, $2, *$3);
                          delete $1; 
                          delete $3;
                          }
                          | STRING INTEGER string_array {
                          driver.routeBlockageNodeLayerCbk(*$1, $2, *$3);
                          delete $1; 
                          delete $3;
                          }
                          | blockage_node_layer_entry EOL 
                          ;

blockage_node_layer_entries : blockage_node_layer_entry
                            | blockage_node_layer_entries blockage_node_layer_entry
                            ;

blockage_node_layer_block : num_blockage_nodes_entry blockage_node_layer_entries
                          ;

route_info_block : grid_entry 
                 | vertical_capacity_entry 
                 | horizontal_capacity_entry 
                 | min_wire_width_entry 
                 | min_wire_spacing_entry 
                 | via_spacing_entry 
                 | grid_origin_entry 
                 | tile_size_entry 
                 | blockage_porosity_entry 
                 ;

/* .route top */
bookshelf_route : route_header 
                | bookshelf_route route_info_block 
                | bookshelf_route pin_layer_block
                | bookshelf_route blockage_node_layer_block
               ; 


/***** .aux file ******/
/* .aux top */
aux_entry : STRING ':' string_array {
              driver.auxCbk(*$1, *$3);
              delete $1;
              delete $3;
              }
              | aux_entry EOL
              ;

bookshelf_aux : aux_entry
              | EOL aux_entry
              ;


 /*** grammar for top file ***/
start : /* empty */
      | bookshelf_nodes
      | bookshelf_nets 
      | bookshelf_pl 
      | bookshelf_scl
      | bookshelf_wts
      | bookshelf_shapes
      | bookshelf_route
      | bookshelf_aux
	  ;

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void BookshelfParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
