file(GLOB SOURCES
    *.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/solvers)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    api/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/solvers/api)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    lpmcf/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/solvers/lpmcf)
endif(INSTALL_LIMBO)
