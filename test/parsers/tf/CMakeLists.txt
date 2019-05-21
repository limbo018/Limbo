include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_tf_spirit test_spirit.cpp)
set_target_properties(test_tf_spirit PROPERTIES OUTPUT_NAME "test_spirit")
install(TARGETS test_tf_spirit DESTINATION test/parsers/tf)

install(DIRECTORY benchmarks DESTINATION test/parsers/tf)
