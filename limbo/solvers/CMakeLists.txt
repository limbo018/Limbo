file(GLOB SOURCES
    *.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/solvers)

file(GLOB SOURCES
    api/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/solvers/api)

file(GLOB SOURCES
    lpmcf/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/solvers/lpmcf)
