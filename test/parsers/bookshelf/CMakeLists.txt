include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_bookshelf_bison test_bison.cpp)
set_target_properties(test_bookshelf_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_bookshelf_bison bookshelfparser ${Boost_LIBRARIES})
install(TARGETS test_bookshelf_bison DESTINATION test/parsers/bookshelf)

install(DIRECTORY benchmarks DESTINATION test/parsers/bookshelf)
