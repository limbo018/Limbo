file(GLOB SOURCES
    *.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/math)
endif(INSTALL_LIMBO)
