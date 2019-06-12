include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/limbo/thirdparty/lemon
    ${PROJECT_BINARY_DIR}/limbo/thirdparty/lemon
    )
set(LIBS lpparser)

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(COMPILE_DEFINITIONS DEBUG_DUALMINCOSTFLOW DEBUG_MINCOSTFLOW)
else()
    set(COMPILE_DEFINITIONS "")
endif()

add_executable(test_DualMinCostFlow test_DualMinCostFlow.cpp)
target_link_libraries(test_DualMinCostFlow ${LIBS} lemon)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_DualMinCostFlow PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_DualMinCostFlow DESTINATION test/solvers)
endif(INSTALL_LIMBO)

add_executable(test_MinCostFlow test_MinCostFlow.cpp)
target_link_libraries(test_MinCostFlow ${LIBS} lemon)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_MinCostFlow PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_MinCostFlow DESTINATION test/solvers)
endif(INSTALL_LIMBO)

add_executable(test_MultiKnapsackLagRelax test_MultiKnapsackLagRelax.cpp)
target_link_libraries(test_MultiKnapsackLagRelax ${LIBS} lemon)
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_MultiKnapsackLagRelax PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_MultiKnapsackLagRelax DESTINATION test/solvers)
endif(INSTALL_LIMBO)

add_executable(test_solvers test_solvers.cpp)
target_link_libraries(test_solvers ${LIBS})
if(COMPILE_DEFINITIONS)
    target_compile_definitions(test_solvers PRIVATE ${COMPILE_DEFINITIONS})
endif(COMPILE_DEFINITIONS)
if(INSTALL_LIMBO)
    install(TARGETS test_solvers DESTINATION test/solvers)
endif(INSTALL_LIMBO)

if (GUROBI_FOUND)
    include_directories(
        ${GUROBI_INCLUDE_DIRS}
        )
    add_executable(test_GurobiApi test_GurobiApi.cpp)
    target_link_libraries(test_GurobiApi ${LIBS} ${GUROBI_LIBRARIES})
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        target_compile_definitions(test_GurobiApi PRIVATE DEBUG_GUROBIAPI=1)
    endif()
    if(INSTALL_LIMBO)
        install(TARGETS test_GurobiApi DESTINATION test/solvers)
    endif(INSTALL_LIMBO)
endif(GUROBI_FOUND)

if (LPSOLVE_FOUND)
    include_directories(
        ${LPSOLVE_INCLUDE_DIRS}
        )
    add_executable(test_LPSolveApi test_LPSolveApi.cpp)
    target_link_libraries(test_LPSolveApi ${LIBS} ${LPSOLVE_LIBRARIES})
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        target_compile_definitions(test_LPSolveApi PRIVATE DEBUG_LPSOLVEAPI=1)
    endif()
    if(INSTALL_LIMBO)
        install(TARGETS test_LPSolveApi DESTINATION test/solvers)
    endif(INSTALL_LIMBO)
endif(LPSOLVE_FOUND)

if(INSTALL_LIMBO)
    install(DIRECTORY benchmarks DESTINATION test/solvers)
endif(INSTALL_LIMBO)

add_subdirectory(lpmcf)
