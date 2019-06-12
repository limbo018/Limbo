file(GLOB SOURCES
    *.h 
    )
install(FILES ${SOURCES} DESTINATION include/limbo/algorithms)

file(GLOB SOURCES
    coloring/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/coloring)

file(GLOB SOURCES
    partition/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/partition)

file(GLOB SOURCES
    placement/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/placement)
