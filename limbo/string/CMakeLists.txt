file(GLOB SOURCES
    *.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/string)
endif(INSTALL_LIMBO)
