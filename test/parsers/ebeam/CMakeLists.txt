include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_ebeam_bison test_bison.cpp)
set_target_properties(test_ebeam_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_ebeam_bison ebeamparser ${Boost_LIBRARIES})
install(TARGETS test_ebeam_bison DESTINATION test/parsers/ebeam)

add_executable(test_ebeam_spirit test_spirit.cpp)
set_target_properties(test_ebeam_spirit PROPERTIES OUTPUT_NAME "test_spirit")
install(TARGETS test_ebeam_spirit DESTINATION test/parsers/ebeam)

install(DIRECTORY benchmarks DESTINATION test/parsers/ebeam)
