file(GLOB SOURCES
    *.h 
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/algorithms)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    coloring/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/coloring)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    partition/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/partition)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    placement/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/algorithms/placement)
endif(INSTALL_LIMBO)
