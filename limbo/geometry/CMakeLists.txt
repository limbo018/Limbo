include_directories(
    ${PROJECT_SOURCE_DIR}
    )
add_library(GeoBoostPolygonApi api/GeoBoostPolygonApi.cpp)
if(INSTALL_LIMBO)
    install(TARGETS GeoBoostPolygonApi DESTINATION lib)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    *.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/geometry)
endif(INSTALL_LIMBO)

file(GLOB SOURCES
    api/*.h
    )
if(INSTALL_LIMBO)
    install(FILES ${SOURCES} DESTINATION include/limbo/geometry/api)
endif(INSTALL_LIMBO)
