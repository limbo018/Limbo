#### Taken from http://www.openflipper.org/svnrepo/CoMISo/trunk/CoMISo/cmake/FindCPLEX.cmake


# - Try to find CPLEX
# Once done this will define
#  CPLEX_FOUND - System has CPLEX
#  CPLEX_INCLUDE_DIRS - The CPLEX include directories
#  CPLEX_LIBRARIES - The libraries needed to use CPLEX

set(CPLEX_FOUND FALSE)
if (CPLEX_INCLUDE_DIR)
    # in cache already
    set(CPLEX_FOUND TRUE)
    set(CPLEX_INCLUDE_DIRS "${CPLEX_INCLUDE_DIR}" )
    set(CPLEX_LIBRARIES "${CPLEX_CXX_LIBRARY};${CPLEX_LIBRARY}" )
  else (CPLEX_INCLUDE_DIR)

    find_path(CPLEX_INCLUDE_DIR 
        NAMES cplex.h
        PATHS "$ENV{CPLEX_HOME}/include"
        )

    # hints of names from version 1000 to 9999
    set(CPLEX_NAME_HINTS "")
    foreach(CPLEX_VERSION RANGE 1000 9999)
        list(APPEND CPLEX_NAME_HINTS "cplex")
        list(APPEND CPLEX_NAME_HINTS "cplex${CPLEX_VERSION}")
    endforeach()

    find_library( CPLEX_LIBRARY 
      NAMES ${CPLEX_NAME_HINTS}
      PATHS "$ENV{CPLEX_HOME}/lib" "$ENV{CPLEX_HOME}/bin" 
      )

    find_library( CPLEX_CXX_LIBRARY 
      NAMES "ilocplex"
      PATHS "$ENV{CPLEX_HOME}/lib" 
      )

    if (CPLEX_INCLUDE_DIR AND CPLEX_LIBRARY AND CPLEX_CXX_LIBRARY)
      set(CPLEX_FOUND TRUE)
      set(CPLEX_INCLUDE_DIRS "${CPLEX_INCLUDE_DIR}" )
      set(CPLEX_LIBRARIES "${CPLEX_CXX_LIBRARY};${CPLEX_LIBRARY}" )

      mark_as_advanced(CPLEX_INCLUDE_DIR CPLEX_LIBRARY CPLEX_CXX_LIBRARY)
    endif(CPLEX_INCLUDE_DIR AND CPLEX_LIBRARY AND CPLEX_CXX_LIBRARY)

    include(FindPackageHandleStandardArgs)
    # handle the QUIETLY and REQUIRED arguments and set LIBCPLEX_FOUND to TRUE
    # if all listed variables are TRUE
    find_package_handle_standard_args(CPLEX  DEFAULT_MSG
      CPLEX_LIBRARY CPLEX_CXX_LIBRARY CPLEX_INCLUDE_DIR)

endif(CPLEX_INCLUDE_DIR)
