include_directories(
    ${PROJECT_SOURCE_DIR}
    )
set(LIBS lpparser)

add_executable(test_lpmcf test_lpmcf.cpp)
target_link_libraries(test_lpmcf ${LIBS} lemon)
install(TARGETS test_lpmcf DESTINATION test/solvers/lpmcf)
install(DIRECTORY benchmarks DESTINATION test/solvers/lpmcf)
