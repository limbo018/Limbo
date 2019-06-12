include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_GDFPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_gdf_bison test_bison.cpp)
set_target_properties(test_gdf_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_gdf_bison gdfparser ${Boost_LIBRARIES})
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_gdf_bison PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_gdf_bison DESTINATION test/parsers/gdf)
    install(DIRECTORY benchmarks DESTINATION test/parsers/gdf)
endif(INSTALL_LIMBO)
