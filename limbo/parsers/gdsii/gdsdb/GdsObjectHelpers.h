/*************************************************************************
    > File Name: GdsObjectHelpers.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 07 Oct 2016 11:42:47 AM CEST
 ************************************************************************/

#ifndef LIMBO_PARSERS_GDSII_GDSDB_GDSOBJECTHELPERS_H
#define LIMBO_PARSERS_GDSII_GDSDB_GDSOBJECTHELPERS_H

#include <cmath>
#include <boost/geometry/strategies/transform.hpp>
#include <limbo/parsers/gdsii/stream/GdsReader.h>
#include <limbo/parsers/gdsii/stream/GdsWriter.h>
#include <limbo/preprocessor/Msg.h>

namespace limbo { namespace GdsParser {

/// some helper functions to convert base class pointers to derived class pointers 
/// the basic procedure is to cast the pointer and perform actions 
/// with template classes, we only need to implement copyable action classes 

struct GdsObjectHelpers
{
	template <typename ActionType>
	void operator()(::GdsParser::GdsRecords::EnumType type, GdsObject* object, ActionType action) const 
	{
		try
		{
			switch (type)
			{
				case ::GdsParser::GdsRecords::BOUNDARY:
					{
						GdsPolygon* ptr = dynamic_cast<GdsPolygon*>(object); 
						action(type, ptr); 
					}
					break;
				case ::GdsParser::GdsRecords::PATH:
					{
						GdsPath* ptr = dynamic_cast<GdsPath*>(object); 
						action(type, ptr); 
					}
					break;
				case ::GdsParser::GdsRecords::TEXT:
					{
						GdsText* ptr = dynamic_cast<GdsText*>(object); 
						action(type, ptr); 
					}
					break;
				case ::GdsParser::GdsRecords::SREF:
					{
						GdsCellReference* ptr = dynamic_cast<GdsCellReference*>(object); 
						action(type, ptr); 
					}
					break;
				case ::GdsParser::GdsRecords::AREF:
					{
						GdsCellArray* ptr = dynamic_cast<GdsCellArray*>(object); 
						action(type, ptr); 
					}
					break;
				default:
					limboAssertMsg(0, "unsupported type %d\n", type); 
			}
		}
		catch (std::exception& e)
		{
			limboPrint(kERROR, "exception in action %s: %s\n", action.message().c_str(), e.what()); 
			limboAssert(0);
		}
	}
};

/// an action function for copy a cell 
struct CopyCellObjectAction
{
	std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*>& target; 

	/// constructor 
	CopyCellObjectAction(std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*>& t) : target(t) {}
	/// copy constructor 
	CopyCellObjectAction(CopyCellObjectAction const& rhs) : target(rhs.target) {}

	template <typename ObjectType>
	void operator()(::GdsParser::GdsRecords::EnumType type, ObjectType* object)
	{
		target.first = type;
		target.second = new ObjectType(*object); 
	}

	/// a message of action for debug 
	std::string message() const 
	{
		return "CopyCellObjectAction"; 
	}
}; 

/// an action function for delete a cell 
struct DeleteCellObjectAction
{
	std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*>& target; 

	/// constructor 
	DeleteCellObjectAction(std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*>& t) : target(t) {}
	/// copy constructor 
	DeleteCellObjectAction(DeleteCellObjectAction const& rhs) : target(rhs.target) {}

	template <typename ObjectType>
	void operator()(::GdsParser::GdsRecords::EnumType /*type*/, ObjectType* object)
	{
		delete object; 
	}

	/// a message of action for debug 
	std::string message() const 
	{
		return "DeleteCellObjectAction"; 
	}
}; 

/// an action function for write a cell 
template <typename GdsWriterType>
struct WriteCellObjectAction
{
	GdsWriterType const& writer; 
	::GdsParser::GdsWriter& gdsWriter; 
	std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*> const& target; 

	/// constructor 
	WriteCellObjectAction(GdsWriterType const& w, ::GdsParser::GdsWriter& gw, std::pair< ::GdsParser::GdsRecords::EnumType, GdsObject*> const& t) : writer(w), gdsWriter(gw), target(t) {}
	/// copy constructor 
	WriteCellObjectAction(WriteCellObjectAction const& rhs) : writer(rhs.writer), gdsWriter(rhs.gdsWriter), target(rhs.target) {}

	template <typename ObjectType>
	void operator()(::GdsParser::GdsRecords::EnumType /*type*/, ObjectType* object)
	{
		writer.write(gdsWriter, *object); 
	}

	/// a message of action for debug 
	std::string message() const 
	{
		return "WriteCellObjectAction"; 
	}
}; 

/// an action function for extract objects of a cell 
namespace ExtractCellObjectActionDetails {

/// default action is to copy objects 
template <typename ObjectType>
inline void extract(GdsDB const& /*gdsDB*/, GdsCell const& /*srcCell*/, GdsCell& targetCell, ::GdsParser::GdsRecords::EnumType type, ObjectType* object)
{
	ObjectType* ptr = new ObjectType (*object); 
	targetCell.objects().push_back(std::make_pair(type, ptr)); 
}

/// specialization for SREF 
template <>
inline void extract<GdsCellReference>(GdsDB const& gdsDB, GdsCell const& srcCell, GdsCell& targetCell, ::GdsParser::GdsRecords::EnumType type, GdsCellReference* object)
{
	limboAssert(type == ::GdsParser::GdsRecords::SREF);
	limboAssertMsg(srcCell.name() != object->refCell(), "self reference of cell %s", srcCell.name().c_str());
	GdsCell const* refCell = gdsDB.getCell(object->refCell()); 
	limboAssertMsg(refCell, "failed to find reference cell %s", object->refCell().c_str());
	// generate a new cell from reference 
	GdsCell cell = object->extractCellRef(gdsDB, *refCell); 
	// directly append object pointers to target cell 
	targetCell.objects().insert(targetCell.objects().end(), cell.objects().begin(), cell.objects().end()); 
	// must clear the list, otherwise, the pointers are destroyed 
	cell.objects().clear(); 
}

/// specialization for AREF 
template <>
inline void extract<GdsCellArray>(GdsDB const& /*gdsDB*/, GdsCell const& /*srcCell*/, GdsCell& /*targetCell*/, ::GdsParser::GdsRecords::EnumType type, GdsCellArray* /*object*/)
{
	limboAssert(type == ::GdsParser::GdsRecords::AREF);
	limboAssertMsg(0, "not implemented yet"); 
}

}

struct ExtractCellObjectAction
{
	GdsDB const& gdsDB; 
	GdsCell const& srcCell; 
	GdsCell& targetCell; 

	/// constructor 
	ExtractCellObjectAction(GdsDB const& db, GdsCell const& sc, GdsCell& tc) : gdsDB(db), srcCell(sc), targetCell(tc) {}
	/// copy constructor 
	ExtractCellObjectAction(ExtractCellObjectAction const& rhs) : gdsDB(rhs.gdsDB), srcCell(rhs.srcCell), targetCell(rhs.targetCell) {}

	/// since template specialization for member function is not supported 
	/// I have to use external function within a namespace 
	template <typename ObjectType>
	void operator()(::GdsParser::GdsRecords::EnumType type, ObjectType* object)
	{
		ExtractCellObjectActionDetails::extract(gdsDB, srcCell, targetCell, type, object);
	}

	/// a message of action for debug 
	std::string message() const 
	{
		return "ExtractCellObjectAction"; 
	}
};

/// an action function to apply changes to a copied cell reference 
namespace ApplyCellReferenceActionDetails {

/// transformers 
struct Translate 
{
	GdsCellReference::point_type offset; 

	Translate(GdsCellReference::point_type const& o) : offset(o) {}

	void operator()(GdsCellReference::point_type& p) const 
	{
		p = gtl::construct<GdsCellReference::point_type>(p.x()+offset.x(), p.y()+offset.y());
	}
};
struct Rotate 
{
	double angle; 
	double cosAngle; 
	double sinAngle; 

	Rotate(double a) : angle(a) 
	{
		cosAngle = cos(angle/180.0*M_PI);
		sinAngle = sin(angle/180.0*M_PI);
	}

	/// transformation matrix 
	/// cos(theta) -sin(theta)
	/// sin(theta) cos(theta)
	void operator()(GdsCellReference::point_type& p) const 
	{
		p = gtl::construct<GdsCellReference::point_type>(
				p.x()*cosAngle - p.y()*sinAngle, 
				p.x()*sinAngle + p.y()*cosAngle
				);
	}
};
struct MagScale 
{
	double scaleX; 
	double scaleY; 

	MagScale(double sx, double sy) : scaleX(sx), scaleY(sy) {}

	void operator()(GdsCellReference::point_type& p) const 
	{
		p = gtl::construct<GdsCellReference::point_type>(p.x()*scaleX, p.y()*scaleY);
	}
};
struct XReflection
{
	void operator()(GdsCellReference::point_type& p) const 
	{
		p = gtl::construct<GdsCellReference::point_type>(p.x(), -p.y());
	}
};

template <typename Iterator, typename TransformerType>
inline void transform(Iterator first, Iterator last, TransformerType transform)
{
	for (; first != last; ++first)
		transform(*first);
}

/// copy points of objects to array 
template <typename ObjectType>
inline void copyToArray(std::vector<GdsCellReference::point_type>& vPoint, ObjectType* object)
{
	vPoint.assign(object->begin(), object->end());
}
template <>
inline void copyToArray<GdsText>(std::vector<GdsCellReference::point_type>& vPoint, GdsText* object)
{
	vPoint.assign(1, object->position());
}
/// copy points of objects from array 
template <typename ObjectType>
inline void copyFromArray(std::vector<GdsCellReference::point_type> const& vPoint, ObjectType* object)
{
	object->set(vPoint.begin(), vPoint.end());
}
template <>
inline void copyFromArray<GdsText>(std::vector<GdsCellReference::point_type> const& vPoint, GdsText* object)
{
	object->setPosition(vPoint.front());
}

template <typename ObjectType>
inline void apply(GdsCellReference const& cellRef, ObjectType* object)
{
	std::vector<GdsCellReference::point_type> vPoint; 
	copyToArray(vPoint, object);
	// the order must be kept according to the manual 
	// strans
	if (cellRef.strans() != std::numeric_limits<int>::max() && cellRef.strans()/32768 > 0) // apply x reflection 
	{
		transform(vPoint.begin(), vPoint.end(), XReflection()); 
	}
	// magnification 
	if (cellRef.magnification() != std::numeric_limits<double>::max())
	{
		transform(vPoint.begin(), vPoint.end(), MagScale(cellRef.magnification(), cellRef.magnification())); 
	}
	// angle 
	if (cellRef.angle() != std::numeric_limits<double>::max())
	{
		transform(vPoint.begin(), vPoint.end(), Rotate(cellRef.angle())); 
	}
	// position offset 
	if (cellRef.position().x() != std::numeric_limits<int>::max() && cellRef.position().y() != std::numeric_limits<int>::max())
	{
		transform(vPoint.begin(), vPoint.end(), Translate(cellRef.position())); 
	}
	copyFromArray(vPoint, object);
}

template <>
inline void apply<GdsCellReference>(GdsCellReference const& /*cellRef*/, GdsCellReference* /*object*/)
{
	limboAssertMsg(0, "should not arrive here"); 
}

template <>
inline void apply<GdsCellArray>(GdsCellReference const& /*cellRef*/, GdsCellArray* /*object*/)
{
	limboAssertMsg(0, "should not arrive here"); 
}

}
struct ApplyCellReferenceAction
{
	GdsCellReference const& cellRef; 

	/// constructor 
	ApplyCellReferenceAction(GdsCellReference const& cr) : cellRef(cr) {}
	/// copy constructor 
	ApplyCellReferenceAction(ApplyCellReferenceAction const& rhs) : cellRef(rhs.cellRef) {}

	template <typename ObjectType>
	void operator()(::GdsParser::GdsRecords::EnumType /*type*/, ObjectType* object)
	{
		ApplyCellReferenceActionDetails::apply(cellRef, object);
	}

	/// a message of action for debug 
	std::string message() const 
	{
		return "ApplyCellReferenceAction"; 
	}
};

}} // namespace limbo // GdsParser

#endif
