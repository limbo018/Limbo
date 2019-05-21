cmake_minimum_required(VERSION 3.0.2)

project(Limbo)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message("-- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(Threads REQUIRED)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS iostreams chrono timer unit_test_framework graph regex)
find_package(Gurobi)
find_package(LpSolve)

add_subdirectory(limbo)
add_subdirectory(test)
