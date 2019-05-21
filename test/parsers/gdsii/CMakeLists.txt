include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_gdsii_reader test_reader.cpp)
set_target_properties(test_gdsii_reader PROPERTIES OUTPUT_NAME "test_reader")
target_link_libraries(test_gdsii_reader gdsparser ${Boost_LIBRARIES} ${ZLIB_LIBRARIES})
install(TARGETS test_gdsii_reader DESTINATION test/parsers/gdsii)

add_executable(test_gdsii_writer test_writer.cpp)
set_target_properties(test_gdsii_writer PROPERTIES OUTPUT_NAME "test_writer")
target_link_libraries(test_gdsii_writer gdsparser ${Boost_LIBRARIES} ${ZLIB_LIBRARIES})
install(TARGETS test_gdsii_writer DESTINATION test/parsers/gdsii)

add_executable(test_gdsii_driver test_driver.cpp)
set_target_properties(test_gdsii_driver PROPERTIES OUTPUT_NAME "test_driver")
target_link_libraries(test_gdsii_driver gdsparser ${Boost_LIBRARIES} ${ZLIB_LIBRARIES})
install(TARGETS test_gdsii_driver DESTINATION test/parsers/gdsii)

add_executable(test_gdsii_gdsdb test_gdsdb.cpp)
set_target_properties(test_gdsii_gdsdb PROPERTIES OUTPUT_NAME "test_gdsdb")
target_link_libraries(test_gdsii_gdsdb gdsdb gdsparser ${Boost_LIBRARIES} ${ZLIB_LIBRARIES})
install(TARGETS test_gdsii_gdsdb DESTINATION test/parsers/gdsii)

install(DIRECTORY benchmarks DESTINATION test/parsers/gdsii)
