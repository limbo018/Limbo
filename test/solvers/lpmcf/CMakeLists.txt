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
set(LIBS lpparser ${LIBS})

add_executable(test_lpmcf test_lpmcf.cpp)
target_link_libraries(test_lpmcf PRIVATE ${LIBS} lemon)
if(INSTALL_LIMBO)
    install(TARGETS test_lpmcf DESTINATION test/solvers/lpmcf)
    install(DIRECTORY benchmarks DESTINATION test/solvers/lpmcf)
endif(INSTALL_LIMBO)
