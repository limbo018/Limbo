include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_TFPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_tf_spirit test_spirit.cpp)
set_target_properties(test_tf_spirit PROPERTIES OUTPUT_NAME "test_spirit")
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_tf_spirit PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
install(TARGETS test_tf_spirit DESTINATION test/parsers/tf)

install(DIRECTORY benchmarks DESTINATION test/parsers/tf)
