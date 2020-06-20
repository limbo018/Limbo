cmake_minimum_required(VERSION 3.7.0)

project(Limbo)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, Debug|Release" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
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
option(ENABLE_TEST "Whether enable test, ON|OFF" ON)
message(STATUS "ENABLE_TEST: ${ENABLE_TEST}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads REQUIRED)
find_package(BISON 3.0 REQUIRED)
find_package(FLEX REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS graph regex)
find_package(Gurobi)
find_package(LpSolve)

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
