include_directories(
    ${PROJECT_SOURCE_DIR}
    )
add_library(GeoBoostPolygonApi api/GeoBoostPolygonApi.cpp)
install(TARGETS GeoBoostPolygonApi DESTINATION lib)

file(GLOB SOURCES
    *.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/geometry)

file(GLOB SOURCES
    api/*.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/geometry/api)
