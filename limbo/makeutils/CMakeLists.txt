file(GLOB SOURCES
    *.mk 
    )

if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/makeutils)
endif(INSTALL_LIMBO)
