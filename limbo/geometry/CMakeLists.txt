if(Boost_INCLUDE_DIRS)
    set(INCLUDES ${Boost_INCLUDE_DIRS})
    set(LIBS ${Boost_LIBRARIES})
else(Boost_INCLUDE_DIRS)
    set(LIBS Boost::boost)
endif(Boost_INCLUDE_DIRS)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${INCLUDES}
    )
add_library(GeoBoostPolygonApi api/GeoBoostPolygonApi.cpp)
if(LIBS)
    target_link_libraries(GeoBoostPolygonApi PRIVATE ${LIBS})
endif(LIBS)
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
