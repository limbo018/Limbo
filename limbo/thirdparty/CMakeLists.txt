add_subdirectory(CThreadPool)
if(OPENBLAS)
    # The CMAKE in OpenBLAS is too slow, so use makefile system instead 
    #set(USE_THREAD 0)
    ##set(BUILD_WITHOUT_LAPACK ON)
    #set(BUILD_WITHOUT_CBLAS ON)
    #add_subdirectory(OpenBLAS)
    ## OpenBLAS is installed to /include by default 
    ## create symbolic link 
    #if(INSTALL_LIMBO)
    #    install(CODE
    #        "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/include/openblas ${CMAKE_INSTALL_PREFIX}/include/limbo/thirdparty/OpenBLAS)"
    #        )
    #endif(INSTALL_LIMBO)

    enable_language(Fortran)
    #include(${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS/f_check.cmake)
    #include(${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS/fc.cmake)
    set(OPENBLAS_DIR ${CMAKE_CURRENT_BINARY_DIR}/OpenBLAS)
    set(OpenBLAS_LIBNAME ${OPENBLAS_DIR}/libopenblas-st.a)

    add_custom_command(OUTPUT ${OpenBLAS_LIBNAME}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OPENBLAS_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS ${OPENBLAS_DIR}
        COMMAND make -C ${OPENBLAS_DIR} -f ${OPENBLAS_DIR}/Makefile BINARY=64 CC=${CMAKE_C_COMPILER} FC=${CMAKE_Fortran_COMPILER} USE_OPENMP=0 USE_THREAD=0 NO_CBLAS=1 NO_WARMUP=1 libs netlib
        COMMAND ${CMAKE_COMMAND} -E copy ${OPENBLAS_DIR}/libopenblas.a ${OpenBLAS_LIBNAME}
        #WORKING_DIRECTORY ${OPENBLAS_DIR}
        #DEPENDS ${OPENBLAS_SOURCES}
        )

    add_custom_target(openblas_target ALL DEPENDS ${OpenBLAS_LIBNAME}
        )
    add_library(openblas STATIC IMPORTED GLOBAL)
    add_dependencies(openblas openblas_target)
    # specify where the library is and where to find the headers
    set_target_properties(openblas
        PROPERTIES
        IMPORTED_LOCATION ${OpenBLAS_LIBNAME}
        )

    if(INSTALL_LIMBO)
        install(
            FILES ${OpenBLAS_LIBNAME} DESTINATION lib
            )
    endif(INSTALL_LIMBO)

    add_subdirectory(Csdp)
endif(OPENBLAS)
add_subdirectory(dlx)
add_subdirectory(flex)
add_subdirectory(lefdef)
add_subdirectory(libdivide)

set(LEMON_ENABLE_GLPK OFF CACHE STRING "Turn off GLPK for Lemon")
set(LEMON_ENABLE_ILOG OFF CACHE STRING "Turn off ILOG for Lemon")
#set(LEMON_ENABLE_COIN OFF CACHE STRING "Turn off COIN for Lemon")
set(LEMON_ENABLE_SOPLEX OFF CACHE STRING "Turn off SOPLEX for Lemon")
add_subdirectory(lemon)
# lemon is installed to /include by default 
# create symbolic link 
if(INSTALL_LIMBO)
    install(CODE
        "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/include/lemon ${CMAKE_INSTALL_PREFIX}/include/limbo/thirdparty/lemon)"
        )
endif(INSTALL_LIMBO)

add_subdirectory(gzstream)
