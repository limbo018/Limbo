include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )

add_executable(test_lef_bison test_bison.cpp)
set_target_properties(test_lef_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_lef_bison lefparser)
install(TARGETS test_lef_bison DESTINATION test/parsers/lef)

add_executable(test_lef_adapt test_adapt.cpp ${PROJECT_BINARY_DIR}/limbo/parsers/lef/adapt/liblefparseradapt.a)
set_target_properties(test_lef_adapt PROPERTIES OUTPUT_NAME "test_adapt")
target_link_libraries(test_lef_adapt ${PROJECT_BINARY_DIR}/limbo/parsers/lef/adapt/liblefparseradapt.a)
add_dependencies(test_lef_adapt lefparseradapt)
install(TARGETS test_lef_adapt DESTINATION test/parsers/lef)

add_executable(test_lef_spirit test_spirit.cpp)
set_target_properties(test_lef_spirit PROPERTIES OUTPUT_NAME "test_spirit")
install(TARGETS test_lef_spirit DESTINATION test/parsers/lef)

install(DIRECTORY benchmarks DESTINATION test/parsers/lef)
