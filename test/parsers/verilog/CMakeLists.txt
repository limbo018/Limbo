include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_VERILOGPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_verilog_bison test_bison.cpp)
set_target_properties(test_verilog_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_verilog_bison verilogparser ${Boost_LIBRARIES})
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_verilog_bison PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_verilog_bison DESTINATION test/parsers/verilog)
    install(DIRECTORY benchmarks DESTINATION test/parsers/verilog)
endif(INSTALL_LIMBO)
