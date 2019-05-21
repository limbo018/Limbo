include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_lp_bison test_bison.cpp)
set_target_properties(test_lp_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_lp_bison lpparser ${Boost_LIBRARIES})
install(TARGETS test_lp_bison DESTINATION test/parsers/lp)

install(DIRECTORY benchmarks DESTINATION test/parsers/lp)
