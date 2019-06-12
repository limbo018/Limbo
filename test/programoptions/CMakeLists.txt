include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    )
add_executable(test_ProgramOptions test_ProgramOptions.cpp)
target_link_libraries(test_ProgramOptions programoptions)
if(INSTALL_LIMBO)
    install(TARGETS test_ProgramOptions DESTINATION test/programoptions)
endif(INSTALL_LIMBO)

add_executable(test_ProgramOptions_simple test_ProgramOptions_simple)
target_link_libraries(test_ProgramOptions_simple programoptions)
if(INSTALL_LIMBO)
    install(TARGETS test_ProgramOptions_simple DESTINATION test/programoptions)
endif(INSTALL_LIMBO)
