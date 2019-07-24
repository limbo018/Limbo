add_subdirectory(CThreadPool)
if(OPENBLAS)
    set(USE_THREAD 0)
    set(BUILD_WITHOUT_LAPACK ON)
    set(BUILD_WITHOUT_CBLAS ON)
    add_subdirectory(OpenBLAS)
    # OpenBLAS is installed to /include by default 
    # create symbolic link 
    if(INSTALL_LIMBO)
        install(CODE
            "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/include/openblas ${CMAKE_INSTALL_PREFIX}/include/limbo/thirdparty/OpenBLAS)"
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
