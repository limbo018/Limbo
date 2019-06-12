file(GLOB SOURCES
    *.py
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/bibtex)
endif(INSTALL_LIMBO)
