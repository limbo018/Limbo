/*************************************************************************
    > File Name: GdsObjects.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 05 Oct 2016 10:17:53 AM CEST
 ************************************************************************/

#ifndef LIMBO_PARSERS_GDSII_GDSDB_GDSOBJECTS_H
#define LIMBO_PARSERS_GDSII_GDSDB_GDSOBJECTS_H

#include <boost/geometry.hpp>
// use adapted boost.polygon in boost.geometry, which is compatible to rtree
#include <boost/geometry/geometries/adapted/boost_polygon.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <limbo/parsers/gdsii/stream/GdsReader.h>

namespace limbo { namespace GdsParser {

/// some shortcuts for namespace 
namespace gtl = boost::polygon;
namespace bg = boost::geometry;

/// forward declaration 
class GdsCell; 
class GdsDB; 

/*
	Base class for all gdsii objects 
	All data members are initialized to maximum infinity 
*/
class GdsObject 
{
	public:
		/// coordinate types 
		typedef int coordinate_type;
		/// geometry types 
		typedef gtl::point_data<coordinate_type> point_type;
		typedef gtl::interval_data<coordinate_type> interval_type; 
		typedef gtl::rectangle_data<coordinate_type> rectangle_type;
		typedef gtl::polygon_data<coordinate_type> polygon_type;
		typedef gtl::polygon_90_set_data<coordinate_type> polygon_set_type;

		/// default constructor
		GdsObject();
		/// copy constructor 
		GdsObject(GdsObject const&);
		/// assignment 
		GdsObject& operator=(GdsObject const& rhs);
		/// destructor
		/// meaningless to have pure virtual destructor 
		/// because we have to define it anyway 
		virtual ~GdsObject(); 
};

/*
	Base class for all gdsii shapes with layer and datatype attributes  
*/
class GdsShape : public GdsObject
{
	public:
		typedef GdsObject base_type;

		/// default constructor 
		GdsShape();
		/// copy constructor 
		GdsShape(GdsShape const& rhs); 
		/// assignment 
		GdsShape& operator=(GdsShape const& rhs); 
		/// destructor 
		~GdsShape(); 

		/// accessors
		int layer() const {return m_layer;}
		void setLayer(int l) {m_layer = l;}

		int datatype() const {return m_datatype;}
		void setDatatype(int d) {m_datatype = d;}
	protected:
		int m_layer; 
		int m_datatype; 
};

/*
    Rectangular geometric object.

    Parameters
    ----------
    point1 : array-like[2]
        Coordinates of a corner of the rectangle.
    point2 : array-like[2]
        Coordinates of the corner of the rectangle opposite to ``point1``.
    layer : integer
        The GDSII layer number for this element.
    datatype : integer
        The GDSII datatype for this element (between 0 and 255).

    Examples
    --------
    >>> rectangle = gdspy.Rectangle((0, 0), (10, 20))
    >>> myCell.add(rectangle)
*/
class GdsRectangle : public GdsShape, public gtl::rectangle_data<int>
{
	public:
		typedef GdsShape base_type; 
		typedef gtl::rectangle_data<int> base_ext_type; 

		/// default constructor
		GdsRectangle(); 
		/// copy constructor 
		GdsRectangle(GdsRectangle const& rhs); 
		/// assignment 
		GdsRectangle& operator=(GdsRectangle const& rhs);
		/// destructor 
		~GdsRectangle(); 
};

/*
    Polygonal geometric object.

    Parameters
    ----------
    points : array-like[N][2]
        Coordinates of the vertices of the polygon.
    layer : integer
        The GDSII layer number for this element.
    datatype : integer
        The GDSII datatype for this element (between 0 and 255).
    verbose : bool
        If False, warnings about the number of vertices of the polygon will
        be suppressed.

    Notes
    -----
    The last point should not be equal to the first (polygons are
    automatically closed).

    The GDSII specification supports only a maximum of 199 vertices per
    polygon.

    Examples
    --------
    >>> triangle_pts = [(0, 40), (15, 40), (10, 50)]
    >>> triangle = gdspy.Polygon(triangle_pts)
    >>> myCell.add(triangle)
*/
class GdsPolygon : public GdsShape, public gtl::polygon_data<GdsShape::coordinate_type>
{
	public:
		typedef GdsShape base_type; 
		typedef gtl::polygon_data<GdsShape::coordinate_type> base_ext_type; 
		typedef base_type::coordinate_type coordinate_type; 
		typedef base_type::point_type point_type; 

		/// default constructor
		GdsPolygon(); 
		/// copy constructor 
		GdsPolygon(GdsPolygon const& rhs); 
		/// assignment 
		GdsPolygon& operator=(GdsPolygon const& rhs);
		/// destructor 
		~GdsPolygon(); 
};

/*
    Series of geometric objects that form a path or a collection of parallel
    paths.

    Parameters
    ----------
    width : number
        The width of each path.
    initial_point : array-like[2]
        Starting position of the path.
    number_of_paths : positive integer
        Number of parallel paths to create simultaneously.
    distance : number
        Distance between the centers of adjacent paths.

    Attributes
    ----------
    x : number
        Current position of the path in the x direction.
    y : number
        Current position of the path in the y direction.
    w : number
        *Half*-width of each path.
    n : integer
        Number of parallel paths.
    direction : {'+x', '-x', '+y', '-y'} or number
        Direction or angle (in *radians*) the path points to.
    distance : number
        Distance between the centers of adjacent paths.
    length : number
        Length of the central path axis. If only one path is created, this
        is the real length of the path.
*/
class GdsPath : public GdsShape, public bg::model::linestring<GdsShape::point_type>
{
	public:
		typedef GdsShape base_type; 
		typedef bg::model::linestring<GdsShape::point_type> base_ext_type; 

		/// default constructor
		GdsPath(); 
		/// copy constructor 
		GdsPath(GdsPath const& rhs); 
		/// assignment 
		GdsPath& operator=(GdsPath const& rhs);
		/// destructor 
		~GdsPath(); 

		/// accessors 
		int pathtype() const {return m_pathtype;}
		void setPathtype(int p) {m_pathtype = p;}

		coordinate_type width() const {return m_width;}
		void setWidth(coordinate_type w) {m_width = w;}

		template <typename Iterator>
		void set(Iterator first, Iterator last) {this->assign(first, last);}

		/// convert from path to polygon description 
		GdsPolygon toPolygon() const; 
	protected:
		int m_pathtype; 
		coordinate_type m_width; 
};

/*
    Polygonal text object.

    Each letter is formed by a series of polygons.

    Parameters
    ----------
    text : string
        The text to be converted in geometric objects.
    position : array-like[2]
        Text position (lower left corner).
	width : integer 
		Width of the text ?
	presentation : integer 
		Related to the direction of text 
    angle : number
        The angle of rotation of the text.
    size (replaced by magnification) : number
        Base size of each character.
    x_reflection (replaced by strans) : bool
        If ``True``, the reference is reflected parallel to the x direction
        before being rotated.
    layer : integer
        The GDSII layer number for these elements.
    datatype : integer
        The GDSII datatype for this element (between 0 and 255).

    Examples
    --------
    >>> text = gdspy.Text('Sample text', 20, (-10, -100))
    >>> myCell.add(text)
*/
class GdsText : public GdsShape
{
	public:
		typedef GdsShape base_type; 

		/// default constructor
		GdsText(); 
		/// copy constructor 
		GdsText(GdsText const& rhs); 
		/// assignment 
		GdsText& operator=(GdsText const& rhs);
		/// destructor 
		~GdsText(); 

		/// accessors 
		int texttype() const {return m_texttype;}
		void setTexttype(int t) {m_texttype = t;}

		std::string const& text() const {return m_text;}
		void setText(std::string const& t) {m_text = t;}

		int width() const {return m_width;}
		void setWidth(int w) {m_width = w;}

		point_type const& position() const {return m_position;}
		void setPosition(point_type const& p) {m_position = p;}

		int presentation() const {return m_presentation;}
		void setPresentation(int p) {m_presentation = p;}

		double angle() const {return m_angle;}
		void setAngle(double a) {m_angle = a;}

		double magnification() const {return m_magnification;}
		void setMagnification(double m) {m_magnification = m;}

		int strans() const {return m_strans;}
		void setStrans(int s) {m_strans = s;}
	protected:
		int m_texttype; 
		std::string m_text; 
		point_type m_position; 
		int m_width; 
		int m_presentation; 
		double m_angle; 
		double m_magnification; 
		int m_strans; 
};

/*
    Simple reference to an existing cell.

    Parameters
    ----------
    ref_cell : ``Cell`` or string
        The referenced cell or its name.
    origin (replaced with position) : array-like[2]
        Position where the reference is inserted.
    angle : number
        Angle of rotation of the reference (in *degrees*).
    magnification : number
        Magnification factor for the reference.
    x_reflection (replaced by strans) : bool
        If ``True``, the reference is reflected parallel to the x direction
        before being rotated.
*/
class GdsCellReference : public GdsObject
{
	public:
		typedef GdsObject base_type; 

		/// default constructor
		GdsCellReference(); 
		/// copy constructor 
		GdsCellReference(GdsCellReference const& rhs); 
		/// assignment 
		GdsCellReference& operator=(GdsCellReference const& rhs);
		/// destructor 
		~GdsCellReference(); 

		/// accessors 
		std::string const& refCell() const {return m_refCell;}
		void setRefCell(std::string const& r) {m_refCell = r;}

		point_type const& position() const {return m_position;}
		void setPosition(point_type const& p) {m_position = p;}

		double angle() const {return m_angle;}
		void setAngle(double a) {m_angle = a;}

		double magnification() const {return m_magnification;}
		void setMagnification(double m) {m_magnification = m;}

		int strans() const {return m_strans;}
		void setStrans(int s) {m_strans = s;}

		/// extract cell objects from reference cell 
		/// consider rotation and position offset 
		GdsCell extractCellRef(GdsDB const& gdsDB, GdsCell const& srcCell) const; 
	protected:
		std::string m_refCell; 
		point_type m_position; 
		double m_angle; 
		double m_magnification; 
		int m_strans; 
};

/*
    Multiple references to an existing cell in an array format.

    Parameters
    ----------
    ref_cell : ``Cell`` or string
        The referenced cell or its name.
    columns : positive integer
        Number of columns in the array.
    rows : positive integer
        Number of columns in the array.
    spacing : array-like[2]
        distances between adjacent columns and adjacent rows.
    origin (replaced with position) : array-like[2]
        Position where the cell is inserted.
    angle : number
        Angle of rotation of the reference (in *degrees*).
    magnification : number
        Magnification factor for the reference.
    x_reflection (replaced by strans) : bool
        If ``True``, the reference is reflected parallel to the x direction
        before being rotated.
*/
class GdsCellArray : public GdsObject
{
	public:
		typedef GdsObject base_type; 

		/// default constructor
		GdsCellArray(); 
		/// copy constructor 
		GdsCellArray(GdsCellArray const& rhs); 
		/// assignment 
		GdsCellArray& operator=(GdsCellArray const& rhs);
		/// destructor 
		~GdsCellArray(); 

		/// accessors 
		std::string const& refCell() const {return m_refCell;}
		void setRefCell(std::string const& r) {m_refCell = r;}

		int columns() const {return m_columns;}
		void setColumns(int c) {m_columns = c;}

		int rows() const {return m_rows;}
		void setRows(int r) {m_rows = r;}

		coordinate_type spacing(unsigned int idx) const {return m_spacing[idx];}
		void setSpacing(unsigned int idx, coordinate_type s) {m_spacing[idx] = s;}

		std::vector<point_type> const& positions() const {return m_vPosition;}
		std::vector<point_type>& positions() {return m_vPosition;}

		double angle() const {return m_angle;}
		void setAngle(double a) {m_angle = a;}

		double magnification() const {return m_magnification;}
		void setMagnification(double m) {m_magnification = m;}

		int strans() const {return m_strans;}
		void setStrans(int s) {m_strans = s;}
	protected:
		std::string m_refCell; 
		int m_columns; 
		int m_rows; 
		coordinate_type m_spacing[2]; 
		std::vector<point_type> m_vPosition; 
		double m_angle; 
		double m_magnification; 
		int m_strans; 
};

/*
    Collection of elements, both geometric objects and references to other
    cells.

    Parameters
    ----------
    name : string
        The name of the cell.
    exclude_from_global : bool
        If ``True``, the cell will not be included in the global list of
        cells maintained by ``gdspy``.
*/
class GdsCell : public GdsObject
{
	public:
		typedef GdsObject base_type; 
		typedef std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*> object_entry_type; 

		/// default constructor
		GdsCell(); 
		/// copy constructor 
		GdsCell(GdsCell const& rhs); 
		/// assignment 
		GdsCell& operator=(GdsCell const& rhs);
		/// destructor 
		~GdsCell(); 

		void addPolygon(int layer, int datatype, std::vector<point_type> const& vPoint); 
		void addPath(int layer, int datatype, int pathtype, int width, std::vector<point_type> const& vPoint);
		void addText(int layer, int datatype, int texttype, std::string const& str, point_type const& position, int width, int presentation, double angle, double magnification, int strans); 
		void addCellReference(std::string const& sname, point_type const& position, double angle, double magnification, int strans); 
		void addCellArray(std::string const& sname, int columns, int rows, int spacing[2], std::vector<point_type> const& vPosition, double angle, double magnification, int strans); 

		/// accessors 
		std::string const& name() const {return m_name;}
		void setName(std::string const& n) {m_name = n;}

		std::vector<std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*> > const& objects() const {return m_vObject;}
		std::vector<std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*> >& objects() {return m_vObject;}
	protected:
		/// copy 
		void copy(GdsCell const& rhs); 
		/// destroy objects in m_vObject
		void destroy(); 

		std::string m_name; 
		std::vector<object_entry_type> m_vObject; ///< gdsii objects with types 
};

/*
	Top level gdsii database 

    Parameters
    ----------
    header : string
        The header of gdsii file.
	libname : string 
		The name of gdsii library 
	unit : float 
		The user unit, not very useful  
	precision : float 
		The database unit in meter 
*/
class GdsDB : public GdsObject
{
	public:
		typedef GdsObject base_type; 

		/// constructor 
		GdsDB();
		/// copy constructor 
		GdsDB(GdsDB const& rhs);
		/// assignment 
		GdsDB& operator=(GdsDB const& rhs);
		/// destructor 
		~GdsDB();

		/// add a cell and return the reference to the new cell 
		GdsCell& addCell(std::string const& name = ""); 
        GdsCell& addCell(GdsCell const& cell); 

		/// accessors 
		std::string const& header() const {return m_header;}
		void setHeader(std::string const& h) {m_header = h;}
		void setHeader(int h); 

		std::string const& libname() const {return m_libname;}
		void setLibname(std::string const& n) {m_libname = n;}

		double unit() const {return m_unit;}
		void setUnit(double u) {m_unit = u;}

		double precision() const {return m_precision;}
		void setPrecision(double p) {m_precision = p;}

		std::vector<GdsCell> const& cells() const {return m_vCell;}
		std::vector<GdsCell>& cells() {return m_vCell;}

		/// given cell name and return the pointer to the cell 
		/// return NULL if not found 
		GdsCell const* getCell(std::string const& cellName) const; 
		GdsCell* getCell(std::string const& cellName); 

		/// extract a cell into a new cell with flatten hierarchies 
		GdsCell extractCell(std::string const& cellName) const; 
	protected:
		std::string m_header; 
		std::string m_libname; 
		double m_unit; 
		double m_precision; 
		std::vector<GdsCell> m_vCell; ///< cell array  
		std::map<std::string, unsigned int> m_mCellName2Idx; ///< map from cell name to index 
};

}} // namespace limbo // GdsParser


/// Boost.Geometry 
namespace boost { namespace geometry { namespace traits {

//////// for GdsRectangle ////////
template <>
struct tag<limbo::GdsParser::GdsRectangle > : public tag<limbo::GdsParser::GdsRectangle::base_ext_type>
{};

template <>
struct point_type<limbo::GdsParser::GdsRectangle >
{
    typedef limbo::GdsParser::GdsRectangle::point_type type;
};

//////// for GdsPolygon ////////
template <>
struct tag<limbo::GdsParser::GdsPolygon > : public tag<limbo::GdsParser::GdsPolygon::base_ext_type>
{};

template <>
struct point_type<limbo::GdsParser::GdsPolygon >
{
    typedef limbo::GdsParser::GdsObject::point_type type;
};

}}} // namespace boost // namespace geometry // namespace traits

/// Boost.Polygon
namespace boost { namespace polygon {

/// necessary for customized rectangle types 
template <>
struct geometry_concept<limbo::GdsParser::GdsRectangle> 
{
	typedef rectangle_concept type;
};

template <>
struct geometry_concept<limbo::GdsParser::GdsPolygon> 
{
	typedef polygon_concept type;
};

}} // namespace boost // namespace polygon

#endif
