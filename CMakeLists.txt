cmake_minimum_required(VERSION 3.7.0)

project(Limbo)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, Debug|Release" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# deal with GCC dual ABI issue 
if(NOT CMAKE_CXX_ABI)
    set(CMAKE_CXX_ABI 0 CACHE STRING
        "Choose the value for _GLIBCXX_USE_CXX11_ABI, options are: 0|1."
        FORCE)
endif(NOT CMAKE_CXX_ABI)
message(STATUS "CMAKE_CXX_ABI: _GLIBCXX_USE_CXX11_ABI=${CMAKE_CXX_ABI}")
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=${CMAKE_CXX_ABI})


# packages like Csdp and SDPColoringCsdp are dependent to OPENBLAS
option(OPENBLAS "Choose to enable OpenBLAS or not, ON|OFF" OFF)
message(STATUS "OPENBLAS: ${OPENBLAS}")

# whether install the library or not 
option(INSTALL_LIMBO "Whether install ${PROJECT_NAME} or not, ON|OFF" ON)
message(STATUS "INSTALL_LIMBO: ${INSTALL_LIMBO}")

# whether generate documentations 
option(GENERATE_DOCS "Whether generate documentations, ON|OFF" ON)
message(STATUS "GENERATE_DOCS: ${GENERATE_DOCS}")

# whether compile test component 
option(ENABLE_TEST "Whether enable test, ON|OFF" OFF)
message(STATUS "ENABLE_TEST: ${ENABLE_TEST}")

# switches for each package 
message(STATUS "Statistics of Limbo packages")

option(ALGORITHMS "Whether compile Algorithms or not, ON|OFF" ON)
message(STATUS "ALGORITHMS: ${ALGORITHMS}")

option(GEOMETRY "Whether compile Geometry or not, ON|OFF" ON)
message(STATUS "GEOMETRY: ${GEOMETRY}")

option(PROGRAMOPTIONS "Whether compile ProgramOptions or not, ON|OFF" ON)
message(STATUS "PROGRAMOPTIONS: ${PROGRAMOPTIONS}")

option(SOLVERS "Whether compile Solvers or not, ON|OFF" ON)
message(STATUS "SOLVERS: ${SOLVERS}")

option(PARSERS "Whether compile Parsers or not, ON|OFF" ON)
message(STATUS "PARSERS: ${PARSERS}")

option(PARSER_BOOKSHELF "Whether compile Parser.Bookshelf or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_BOOKSHELF: ${PARSER_BOOKSHELF}")
option(PARSER_BOOKSHELF_BISON "Whether compile Parser.Bookshelf.bison or not, ON|OFF" ${PARSER_BOOKSHELF})
message(STATUS "    PARSER_BOOKSHELF_BISON: ${PARSER_BOOKSHELF_BISON}")

option(PARSER_DEF "Whether compile Parser.DEF or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_DEF: ${PARSER_DEF}")
option(PARSER_DEF_BISON "Whether compile Parser.DEF.bison or not, ON|OFF" ${PARSER_DEF})
message(STATUS "    PARSER_DEF_BISON: ${PARSER_DEF_BISON}")
option(PARSER_DEF_ADAPT "Whether compile Parser.DEF.adapt or not, ON|OFF" ${PARSER_DEF})
message(STATUS "    PARSER_DEF_ADAPT: ${PARSER_DEF_ADAPT}")
option(PARSER_DEF_SPIRIT "Whether compile Parser.DEF.spirit or not, ON|OFF" ${PARSER_DEF})
message(STATUS "    PARSER_DEF_SPIRIT: ${PARSER_DEF_SPIRIT}")

option(PARSER_EBEAM "Whether compile Parser.EBEAM or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_EBEAM: ${PARSER_EBEAM}")
option(PARSER_EBEAM_BISON "Whether compile Parser.EBEAM.bison or not, ON|OFF" ${PARSER_EBEAM})
message(STATUS "    PARSER_EBEAM_BISON: ${PARSER_EBEAM_BISON}")
option(PARSER_EBEAM_SPIRIT "Whether compile Parser.EBEAM.spirit or not, ON|OFF" ${PARSER_EBEAM})
message(STATUS "    PARSER_EBEAM_SPIRIT: ${PARSER_EBEAM_SPIRIT}")

option(PARSER_GDF "Whether compile Parser.GDF or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_GDF: ${PARSER_GDF}")
option(PARSER_GDF_BISON "Whether compile Parser.GDF.bison or not, ON|OFF" ${PARSER_GDF})
message(STATUS "    PARSER_GDF_BISON: ${PARSER_GDF_BISON}")

option(PARSER_GDSII "Whether compile Parser.GDSII or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_GDSII: ${PARSER_GDSII}")
option(PARSER_GDSII_STREAM "Whether compile Parser.GDSII.stream or not, ON|OFF" ${PARSER_GDSII})
message(STATUS "    PARSER_GDSII_STREAM: ${PARSER_GDSII_STREAM}")
option(PARSER_GDSII_ASCII "Whether compile Parser.GDSII.ascii or not, ON|OFF" ${PARSER_GDSII})
message(STATUS "    PARSER_GDSII_ASCII: ${PARSER_GDSII_ASCII}")

option(PARSER_LEF "Whether compile Parser.LEF or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_LEF: ${PARSER_LEF}")
option(PARSER_LEF_BISON "Whether compile Parser.LEF.bison or not, ON|OFF" ${PARSER_LEF})
message(STATUS "    PARSER_LEF_BISON: ${PARSER_LEF_BISON}")
option(PARSER_LEF_ADAPT "Whether compile Parser.LEF.adapt or not, ON|OFF" ${PARSER_LEF})
message(STATUS "    PARSER_LEF_ADAPT: ${PARSER_LEF_ADAPT}")
option(PARSER_LEF_SPIRIT "Whether compile Parser.LEF.spirit or not, ON|OFF" ${PARSER_LEF})
message(STATUS "    PARSER_LEF_SPIRIT: ${PARSER_LEF_SPIRIT}")

option(PARSER_LP "Whether compile Parser.LP or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_LP: ${PARSER_LP}")
option(PARSER_LP_BISON "Whether compile Parser.LP.bison or not, ON|OFF" ${PARSER_LP})
message(STATUS "    PARSER_LP_BISON: ${PARSER_LP_BISON}")

option(PARSER_TF "Whether compile Parser.TF.spirit or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_TF: ${PARSER_TF}")
option(PARSER_TF_SPIRIT "Whether compile Parser.TF.spirit or not, ON|OFF" ${PARSER_TF})
message(STATUS "    PARSER_TF_SPIRIT: ${PARSER_TF_SPIRIT}")

option(PARSER_VERILOG "Whether compile Parser.VERILOG or not, ON|OFF" ${PARSERS})
message(STATUS "  PARSER_VERILOG: ${PARSER_VERILOG}")
option(PARSER_VERILOG_BISON "Whether compile Parser.VERILOG.bison or not, ON|OFF" ${PARSER_VERILOG})
message(STATUS "    PARSER_VERILOG_BISON: ${PARSER_VERILOG_BISON}")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads REQUIRED)
find_package(BISON 3.3 REQUIRED)
find_package(FLEX REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS graph regex)
if(ALGORITHMS OR SOLVERS)
find_package(GUROBI)
find_package(CPLEX)
find_package(LPSOLVE)
endif(ALGORITHMS OR SOLVERS)


add_subdirectory(limbo)
if (ENABLE_TEST)
    add_subdirectory(test)
endif (ENABLE_TEST)

if (GENERATE_DOCS)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif(DOXYGEN_FOUND)
endif(GENERATE_DOCS)
