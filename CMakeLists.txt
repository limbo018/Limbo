cmake_minimum_required(VERSION 3.7.0)

project(Limbo)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")

option(CMAKE_BUILD_TYPE "Choose the type of build, Debug|Release" "Release")
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
message("-- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# packages like Csdp and SDPColoringCsdp are dependent to OPENBLAS
option(OPENBLAS "Choose to enable OpenBLAS or not, ON|OFF" ON)
message("-- OPENBLAS: ${OPENBLAS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(Threads REQUIRED)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS iostreams chrono timer unit_test_framework graph regex)
find_package(Gurobi)
find_package(LpSolve)
find_package(Doxygen)

add_subdirectory(limbo)
add_subdirectory(test)

if (DOXYGEN_FOUND)
    add_subdirectory(docs)
endif(DOXYGEN_FOUND)
