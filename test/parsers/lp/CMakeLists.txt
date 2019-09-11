include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_LPPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_lp_bison test_bison.cpp)
set_target_properties(test_lp_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_lp_bison lpparser)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_lp_bison PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_lp_bison DESTINATION test/parsers/lp)
    install(DIRECTORY benchmarks DESTINATION test/parsers/lp)
endif(INSTALL_LIMBO)
