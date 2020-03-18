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
add_executable(test_p2r test_p2r.cpp)
if(LIBS)
    target_link_libraries(test_p2r PRIVATE ${LIBS})
endif(LIBS)
if(INSTALL_LIMBO)
    install(TARGETS test_p2r DESTINATION test/geometry)
endif(INSTALL_LIMBO)

add_executable(test_boostpolygonapi test_boostpolygonapi.cpp)
target_link_libraries(test_boostpolygonapi PRIVATE GeoBoostPolygonApi ${LIBS})
if(INSTALL_LIMBO)
    install(TARGETS test_boostpolygonapi DESTINATION test/geometry)
    install(DIRECTORY benchmarks DESTINATION test/geometry)
endif(INSTALL_LIMBO)
