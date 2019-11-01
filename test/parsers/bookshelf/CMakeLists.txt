include_directories(
    ${PROJECT_SOURCE_DIR}
    )
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_BOOKSHELFPARSER)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_bookshelf_bison test_bison.cpp)
set_target_properties(test_bookshelf_bison PROPERTIES OUTPUT_NAME "test_bison")
target_link_libraries(test_bookshelf_bison bookshelfparser gzstream ${ZLIB_LIBRARIES})
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_bookshelf_bison PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_bookshelf_bison DESTINATION test/parsers/bookshelf)
    install(DIRECTORY benchmarks DESTINATION test/parsers/bookshelf)
endif(INSTALL_LIMBO)
