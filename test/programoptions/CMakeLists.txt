if(Boost_INCLUDE_DIRS)
    set(INCLUDES ${Boost_INCLUDE_DIRS})
    set(LIBS ${Boost_LIBRARIES})
else(Boost_INCLUDE_DIRS)
    set(LIBS Boost::boost)
endif(Boost_INCLUDE_DIRS)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${INCLUDES}
    )
add_executable(test_ProgramOptions test_ProgramOptions.cpp)
target_link_libraries(test_ProgramOptions PRIVATE programoptions ${LIBS})
if(INSTALL_LIMBO)
    install(TARGETS test_ProgramOptions DESTINATION test/programoptions)
endif(INSTALL_LIMBO)

add_executable(test_ProgramOptions_simple test_ProgramOptions_simple.cpp)
target_link_libraries(test_ProgramOptions_simple PRIVATE programoptions ${LIBS})
if(INSTALL_LIMBO)
    install(TARGETS test_ProgramOptions_simple DESTINATION test/programoptions)
endif(INSTALL_LIMBO)
