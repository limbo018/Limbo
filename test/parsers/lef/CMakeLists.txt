include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_LEFPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_lef_bison test_bison.cpp)
set_target_properties(test_lef_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_lef_bison lefparser)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_lef_bison PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
install(TARGETS test_lef_bison DESTINATION test/parsers/lef)

add_executable(test_lef_adapt test_adapt.cpp)
set_target_properties(test_lef_adapt PROPERTIES OUTPUT_NAME "test_adapt")
target_link_libraries(test_lef_adapt ${PROJECT_BINARY_DIR}/limbo/parsers/lef/adapt/liblefparseradapt.a)
add_dependencies(test_lef_adapt lefparseradapt)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_lef_adapt PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
install(TARGETS test_lef_adapt DESTINATION test/parsers/lef)

add_executable(test_lef_spirit test_spirit.cpp)
set_target_properties(test_lef_spirit PROPERTIES OUTPUT_NAME "test_spirit")
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_lef_spirit PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
install(TARGETS test_lef_spirit DESTINATION test/parsers/lef)

install(DIRECTORY benchmarks DESTINATION test/parsers/lef)
