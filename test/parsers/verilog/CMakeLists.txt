include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_verilog_bison test_bison.cpp)
set_target_properties(test_verilog_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_verilog_bison verilogparser ${Boost_LIBRARIES})
install(TARGETS test_verilog_bison DESTINATION test/parsers/verilog)

install(DIRECTORY benchmarks DESTINATION test/parsers/verilog)
