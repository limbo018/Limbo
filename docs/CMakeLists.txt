file(GLOB ORIG_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Readme.md 
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/bibtex/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/containers/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/makeutils/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/math/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/preprocessor/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/programoptions/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/solvers/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/string/* 
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/* 
    ${PROJECT_SOURCE_DIR}/limbo/algorithms/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/algorithms/coloring/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/algorithms/partition/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/algorithms/placement/*.h 
    ${PROJECT_SOURCE_DIR}/test/algorithms/*.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/bibtex/*.py 
    ${PROJECT_SOURCE_DIR}/limbo/containers/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/makeutils/*.mk 
    ${PROJECT_SOURCE_DIR}/limbo/math/*.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/bookshelf/test_bison.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/bookshelf/bison/BookshelfDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/bookshelf/bison/BookshelfDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/def/test_adapt.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/def/adapt/DefDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/def/adapt/DefDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/ebeam/test_bison.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/ebeam/bison/EbeamDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/ebeam/bison/EbeamDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/gdf/test_bison.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/gdf/bison/GdfDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/gdf/bison/GdfDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/gdsii/*.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/gdsii/stream/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/gdsii/gdsdb/*.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/lef/test_adapt.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/lef/adapt/LefDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/lef/adapt/LefDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/lp/test_bison.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/lp/bison/LpDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/lp/bison/LpDriver.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/tf/test_spirit.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/tf/spirit/TfParser.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/tf/spirit/ErrorHandler.h 
    ${PROJECT_SOURCE_DIR}/test/parsers/verilog/test_bison.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/verilog/bison/VerilogDataBase.h 
    ${PROJECT_SOURCE_DIR}/limbo/parsers/verilog/bison/VerilogDriver.h 
    ${PROJECT_SOURCE_DIR}/test/geometry/*.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/geometry/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/geometry/api/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/preprocessor/*.h 
    ${PROJECT_SOURCE_DIR}/test/programoptions/*.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/programoptions/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/solvers/api/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/solvers/lpmcf/*.h 
    ${PROJECT_SOURCE_DIR}/limbo/solvers/*.h 
    ${PROJECT_SOURCE_DIR}/test/solvers/lpmcf/*.cpp 
    ${PROJECT_SOURCE_DIR}/test/solvers/*.cpp 
    ${PROJECT_SOURCE_DIR}/test/string/*.cpp 
    ${PROJECT_SOURCE_DIR}/limbo/string/*.h
    )
string(REPLACE ";" " " SRCS "${ORIG_SRCS}")

file(GLOB ORIG_CITE_BIB_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ref/Top.bib
    ${CMAKE_CURRENT_SOURCE_DIR}/ref/*.bib
    )
string(REPLACE ";" " " CITE_BIB_FILES "${ORIG_CITE_BIB_FILES}")

set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/docs.stamp")

configure_file(${doxyfile_in} ${doxyfile})

add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
    DEPENDS ${ORIG_SRCS} ${ORIG_CITE_BIB_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    )

add_custom_target(doc ALL DEPENDS ${OUTPUT})

if(INSTALL_LIMBO)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION docs)
endif(INSTALL_LIMBO)
