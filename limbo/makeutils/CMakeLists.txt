file(GLOB SOURCES
    *.mk 
    )
install(FILES ${SOURCES} DESTINATION include/limbo/makeutils)
