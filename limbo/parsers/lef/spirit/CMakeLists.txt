file(GLOB SOURCES
    *.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/parsers/lef/spirit)
endif(INSTALL_LIMBO)
