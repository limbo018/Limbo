include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )

add_executable(test_def_bison test_bison.cpp)
set_target_properties(test_def_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_def_bison defparser)
install(TARGETS test_def_bison DESTINATION test/parsers/def)

add_executable(test_def_adapt test_adapt.cpp)
set_target_properties(test_def_adapt PROPERTIES OUTPUT_NAME "test_adapt")
target_link_libraries(test_def_adapt ${PROJECT_BINARY_DIR}/limbo/parsers/def/adapt/libdefparseradapt.a)
add_dependencies(test_def_adapt defparseradapt)
install(TARGETS test_def_adapt DESTINATION test/parsers/def)

add_executable(test_def_spirit test_spirit.cpp)
set_target_properties(test_def_spirit PROPERTIES OUTPUT_NAME "test_spirit")
install(TARGETS test_def_spirit DESTINATION test/parsers/def)

install(DIRECTORY benchmarks DESTINATION test/parsers/def)
