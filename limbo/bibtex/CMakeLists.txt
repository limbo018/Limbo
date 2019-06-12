file(GLOB SOURCES
    *.py
    )
install(FILES ${SOURCES} DESTINATION include/limbo/bibtex)
