include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/limbo/thirdparty/lemon
    ${PROJECT_BINARY_DIR}/limbo/thirdparty/lemon
    )
set(LIBS lpparser)

add_executable(test_DualMinCostFlow test_DualMinCostFlow.cpp)
target_link_libraries(test_DualMinCostFlow ${LIBS} lemon)
install(TARGETS test_DualMinCostFlow DESTINATION test/solvers)

add_executable(test_MinCostFlow test_MinCostFlow.cpp)
target_link_libraries(test_MinCostFlow ${LIBS} lemon)
install(TARGETS test_MinCostFlow DESTINATION test/solvers)

add_executable(test_MultiKnapsackLagRelax test_MultiKnapsackLagRelax.cpp)
target_link_libraries(test_MultiKnapsackLagRelax ${LIBS} lemon)
install(TARGETS test_MultiKnapsackLagRelax DESTINATION test/solvers)

add_executable(test_solvers test_solvers.cpp)
target_link_libraries(test_solvers ${LIBS})
install(TARGETS test_solvers DESTINATION test/solvers)

if (GUROBI_FOUND)
    include_directories(
        ${GUROBI_INCLUDE_DIRS}
        )
    add_executable(test_GurobiApi test_GurobiApi.cpp)
    target_link_libraries(test_GurobiApi ${LIBS} ${GUROBI_LIBRARIES})
    install(TARGETS test_GurobiApi DESTINATION test/solvers)
endif(GUROBI_FOUND)

if (LPSOLVE_FOUND)
    include_directories(
        ${LPSOLVE_INCLUDE_DIRS}
        )
    add_executable(test_LPSolveApi test_LPSolveApi.cpp)
    target_link_libraries(test_LPSolveApi ${LIBS} ${LPSOLVE_LIBRARIES})
    install(TARGETS test_LPSolveApi DESTINATION test/solvers)
endif(LPSOLVE_FOUND)

install(DIRECTORY benchmarks DESTINATION test/solvers)

add_subdirectory(lpmcf)
