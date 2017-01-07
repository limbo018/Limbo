cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "limbo")
project(${PROJECT_NAME})

set(LIMBO_VERSION "2.7.0" CACHE STRING "limbo version string.")
set(PROJECT_VERSION ${LIMBO_VERSION})
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# define directories 

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

message(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# recursive directories 
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_subdirectory(${PROJECT_SOURCE_DIR}/limbo/parsers)
add_subdirectory(${PROJECT_SOURCE_DIR}/limbo/solvers)
add_subdirectory(${PROJECT_SOURCE_DIR}/limbo/programoptions)
add_subdirectory(${PROJECT_SOURCE_DIR}/limbo/thirdparty)

# dependencies 
set(LIMBO_ENABLE_BOOST YES CACHE STRING "Enable Boost.")
set(LIMBO_ENABLE_ZLIB YES CACHE STRING "Enable ZLIB.")

# Boost 
if(BOOST_DIR)
    set(BOOST_ROOT "${BOOST_DIR}")
endif()
find_package(Boost 1.44.0 Minimum)
if(Boost_FOUND)
    message("Boost ------------------ YES, include directory ${Boost_INCLUDE_DIRS}, link directory ${Boost_LIBRARY_DIRS}")
else()
    message("Boost ------------------ NO")
endif()
# ZLIB 
if(ZLIB_DIR)
    set(ZLIB_ROOT "${ZLIB_DIR}")
endif()
find_package(ZLIB)
if(ZLIB_FOUND)
    message("ZLIB ------------------ YES, include directory ${ZLIB_INCLUDE_DIRS}, link ${ZLIB_LIBRARIES}")
else()
    message("ZLIB ------------------ NO")
endif()

# building configurations  
# build type can be DEBUG or RELEASE
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RELEASE")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CXXSTDLIB "-stdlib=libstdc++")
    set(CXXSTD "-std=c++98")
    set(CMAKE_CXX_FLAGS_BASIC "-ferror-limit=1 -fPIC -W -Wall -Wextra -Wreturn-type -m64 ${CXXSTDLIB} ${CXXSTD} -Wno-deprecated -Wno-unused-parameter -Wno-unused-local-typedef")
    set(CMAKE_C_FLAGS_BASIC "-ferror-limit=1 -fPIC -W -Wall -Wextra -Wreturn-type -m64 -Wno-deprecated -Wno-unused-parameter -Wno-unused-local-typedef")
    if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_BASIC} -g -DDEBUG")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_BASIC} -g -DDEBUG")
    elseif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_BASIC} -O3")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_BASIC} -O3")
    endif() 
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CXXSTDLIB "")
    set(CXXSTD "-std=c++98")
    set(CMAKE_CXX_FLAGS_BASIC "-fmax-errors=1 -fPIC -W -Wall -Wextra -Wreturn-type -m64 ${CXXSTDLIB} ${CXXSTD} -Wno-deprecated -Wno-unused-local-typedefs")
    set(CMAKE_C_FLAGS_BASIC "-fmax-errors=1 -fPIC -W -Wall -Wextra -Wreturn-type -ansi -m64 -Wno-deprecated -Wno-unused-local-typedefs")
    if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_BASIC} -g -DDEBUG")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_BASIC} -g -DDEBUG")
    elseif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_BASIC} -O3 -fopenmp")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_BASIC} -O3")
    endif() 
#elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
#    # using Intel C++
#elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#  # using Visual Studio C++
endif()
