/**
 * @file   gdsii/test_gdsdb.cpp
 * @brief  test @ref GdsParser::GdsDB::GdsDB 
 * @author Yibo Lin
 * @date   Jan 2017
 */

#include <iostream>
#include <limbo/parsers/gdsii/gdsdb/GdsIO.h>
#include <limbo/parsers/gdsii/gdsdb/GdsObjectHelpers.h>
#include <limbo/preprocessor/Msg.h>

/// @brief main function 
/// @param argc number of arguments 
/// @param argv values of arguments, 4 arguments: input gds, output gds, flat output gds, flat cell name  
/// @return 0 if succeed 
int main(int argc, char** argv)
{
    GdsParser::GdsDB::GdsDB db; 
    if (argc > 2 && argc <= 4)
    {
        // test simple read and write
        GdsParser::GdsDB::GdsReader reader (db); 
        limboAssert(reader(argv[1]));

        for (std::vector<GdsParser::GdsDB::GdsCell>::const_iterator it = db.cells().begin(); it != db.cells().end(); ++it)
            std::cout << "cell: " << it->name() << std::endl; 

        // write 
        GdsParser::GdsDB::GdsWriter gw (db); 
        gw(argv[2]);

        std::cout << "4 arguments to test flatten: input gds, output gds, flat output gds, flat cell name" << std::endl;
    }
	else if (argc > 4)
    {
        // test simple read and write
        GdsParser::GdsDB::GdsReader reader (db); 
        limboAssert(reader(argv[1]));

        for (std::vector<GdsParser::GdsDB::GdsCell>::const_iterator it = db.cells().begin(); it != db.cells().end(); ++it)
            std::cout << "cell: " << it->name() << std::endl; 

#if 0
        // try removing all text records except for the top cell
        // iterate through all cells 
        for (std::vector<GdsParser::GdsDB::GdsCell>::iterator it = db.cells().begin(); it != db.cells().end(); ++it)
        {
          GdsParser::GdsDB::GdsCell& cell = *it; 
          if (cell.name() != argv[4]) // check the non-top cell 
          {
            // iterate through all objects 
            for (std::vector<GdsParser::GdsDB::GdsCell::object_entry_type>::iterator itc = cell.objects().begin(), itce = cell.objects().end(); itc != itce; ) 
            {
              if (itc->first == ::GdsParser::GdsRecords::TEXT) // find TEXT records
              {
                std::vector<GdsParser::GdsDB::GdsCell::object_entry_type>::iterator itclast = itce - 1; 
                if (itc != itclast) // swap current object with the last object 
                {
                  std::swap(*itc, *itclast); 
                }
                // delete the last object 
                GdsParser::GdsDB::GdsObjectHelpers()(itclast->first, itclast->second, GdsParser::GdsDB::DeleteCellObjectAction(*itclast)); 
                // update the object array in the cell
                cell.objects().pop_back(); 
                // update end iterator 
                itce = cell.objects().end();
              }
              else 
              {
                ++itc; 
              }
            }
          }
        }
#endif

        // test flatten 
        GdsParser::GdsDB::GdsCell flatCell = db.extractCell(argv[4]);

        GdsParser::GdsDB::GdsDB flatDB; 
        flatDB.setLibname(db.libname()); 
        flatDB.setUnit(db.unit()); 
        flatDB.setPrecision(db.precision());
        flatDB.addCell(flatCell); 

        // write flatten cell 
        GdsParser::GdsDB::GdsWriter flatGw (flatDB); 
        flatGw(argv[3]);
    }
	else std::cout << "at least 4 arguments are required: input gds, output gds, flat output gds, flat cell name" << std::endl;

	return 0;
}
