include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_gdf_bison test_bison.cpp)
set_target_properties(test_gdf_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_gdf_bison gdfparser ${Boost_LIBRARIES})
install(TARGETS test_gdf_bison DESTINATION test/parsers/gdf)

install(DIRECTORY benchmarks DESTINATION test/parsers/gdf)
