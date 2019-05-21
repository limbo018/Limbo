add_subdirectory(CThreadPool)
set(USE_THREAD 0)
add_subdirectory(OpenBLAS)
# OpenBLAS is installed to /include by default 
# create symbolic link 
install(CODE
    "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/include/openblas ${CMAKE_INSTALL_PREFIX}/include/limbo/thirdparty/OpenBLAS)"
    )
add_subdirectory(Csdp)
add_subdirectory(dlx)
add_subdirectory(flex)
add_subdirectory(lefdef)
add_subdirectory(libdivide)
add_subdirectory(lemon)
# lemon is installed to /include by default 
# create symbolic link 
install(CODE
    "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/include/lemon ${CMAKE_INSTALL_PREFIX}/include/limbo/thirdparty/lemon)"
    )
