#
## Taken from http://www.openflipper.org/svnrepo/CoMISo/trunk/CoMISo/cmake/FindGUROBI.cmake


# - Try to find GUROBI
# Once done this will define
#  GUROBI_FOUND - System has Gurobi
#  GUROBI_INCLUDE_DIRS - The Gurobi include directories
#  GUROBI_LIBRARIES - The libraries needed to use Gurobi

if (GUROBI_INCLUDE_DIR)
    # in cache already
    set(GUROBI_FOUND TRUE)
    set(GUROBI_INCLUDE_DIRS "${GUROBI_INCLUDE_DIR}" )
    set(GUROBI_LIBRARIES "${GUROBI_CXX_LIBRARY};${GUROBI_LIBRARY}" )
else (GUROBI_INCLUDE_DIR)

    find_path(GUROBI_INCLUDE_DIR 
        NAMES gurobi_c++.h
        PATHS "$ENV{GUROBI_HOME}/include"
        )
    
    message(STATUS "[LIMBO] GUROBI_INCLUDE_DIR: ${GUROBI_INCLUDE_DIR}")
    message(STATUS "[LIMBO] GUROBI_HOME: ${GUROBI_HOME}")
    message(STATUS "[LIMBO] GUROBI_VERSION: ${GUROBI_VERSION}")

    # hints of names from version 40 to 99
    set(GUROBI_NAME_HINTS "")
    foreach(GUROBI_VERSION RANGE 40 110)
        list(APPEND GUROBI_NAME_HINTS "gurobi${GUROBI_VERSION}")
    endforeach()

    find_library( GUROBI_LIBRARY 
        NAMES ${GUROBI_NAME_HINTS}
        PATHS "$ENV{GUROBI_HOME}/lib" 
        )

    find_library( GUROBI_CXX_LIBRARY 
        NAMES gurobi_c++
        PATHS "$ENV{GUROBI_HOME}/lib" 
        )

    if (GUROBI_INCLUDE_DIR AND GUROBI_LIBRARY AND GUROBI_CXX_LIBRARY)
        set(GUROBI_FOUND TRUE)
        set(GUROBI_INCLUDE_DIRS "${GUROBI_INCLUDE_DIR}" )
        set(GUROBI_LIBRARIES "${GUROBI_CXX_LIBRARY};${GUROBI_LIBRARY}" )

        # use c++ headers as default
        # set(GUROBI_COMPILER_FLAGS "-DIL_STD" CACHE STRING "Gurobi Compiler Flags")

        include(FindPackageHandleStandardArgs)
        # handle the QUIETLY and REQUIRED arguments and set LIBCPLEX_FOUND to TRUE
        # if all listed variables are TRUE
        find_package_handle_standard_args(GUROBI  DEFAULT_MSG
            GUROBI_LIBRARY GUROBI_CXX_LIBRARY GUROBI_INCLUDE_DIR)

        mark_as_advanced(GUROBI_INCLUDE_DIR GUROBI_LIBRARY GUROBI_CXX_LIBRARY)
    endif(GUROBI_INCLUDE_DIR AND GUROBI_LIBRARY AND GUROBI_CXX_LIBRARY)

endif(GUROBI_INCLUDE_DIR)

message(STATUS "[LIMBO] GUROBI_LIBRARIES: ${GUROBI_LIBRARIES}")
