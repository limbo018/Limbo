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
add_executable(test_string test_string.cpp)
add_executable(test_compare test_compare.cpp)
if(LIBS)
    target_link_libraries(test_string PRIVATE ${LIBS})
    target_link_libraries(test_compare PRIVATE ${LIBS})
endif(LIBS)
if(INSTALL_LIMBO)
    install(TARGETS test_string test_compare DESTINATION test/string)
endif(INSTALL_LIMBO)
