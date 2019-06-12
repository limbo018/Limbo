include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_string test_string.cpp)
add_executable(test_compare test_compare.cpp)
if(INSTALL_LIMBO)
    install(TARGETS test_string test_compare DESTINATION test/string)
endif(INSTALL_LIMBO)
