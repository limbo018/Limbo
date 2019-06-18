include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_p2r test_p2r.cpp)
if(INSTALL_LIMBO)
    install(TARGETS test_p2r DESTINATION test/geometry)
endif(INSTALL_LIMBO)

add_executable(test_boostpolygonapi test_boostpolygonapi.cpp)
target_link_libraries(test_boostpolygonapi GeoBoostPolygonApi)
if(INSTALL_LIMBO)
    install(TARGETS test_boostpolygonapi DESTINATION test/geometry)
    install(DIRECTORY benchmarks DESTINATION test/geometry)
endif(INSTALL_LIMBO)
