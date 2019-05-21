include_directories(
    ${PROJECT_SOURCE_DIR}
    )
set(LIBS ${Boost_LIBRARIES} sdp openblas m ${CMAKE_THREAD_LIBS_INIT} gfortran)
if(UNIX AND NOT APPLE)
    set(LIBS ${LIBS} rt)
endif()

add_executable(test_ChromaticNumber test_ChromaticNumber.cpp)
target_link_libraries(test_ChromaticNumber LINK_PUBLIC ${LIBS})
install(TARGETS test_ChromaticNumber DESTINATION test/algorithms)

add_executable(test_GraphSimplification test_GraphSimplification.cpp)
target_link_libraries(test_GraphSimplification LINK_PUBLIC ${LIBS})
install(TARGETS test_GraphSimplification DESTINATION test/algorithms)

add_executable(test_FM test_FM.cpp)
target_link_libraries(test_FM LINK_PUBLIC ${LIBS})
install(TARGETS test_FM DESTINATION test/algorithms)

add_executable(test_SDPColoring test_SDPColoring.cpp)
target_link_libraries(test_SDPColoring LINK_PUBLIC ${LIBS})
install(TARGETS test_SDPColoring DESTINATION test/algorithms)

if(GUROBI_FOUND)
    include_directories(
        ${GUROBI_INCLUDE_DIRS}
        )
    set(LIBS ${GUROBI_LIBRARIES} ${LIBS})

    # LPColoring is only available for C++98 yet 
    #add_executable(test_LPColoring test_LPColoring.cpp)
    #target_link_libraries(test_LPColoring LINK_PUBLIC ${LIBS})
    #install(TARGETS test_LPColoring DESTINATION test/algorithms)

    add_executable(test_ILPColoring test_ILPColoring.cpp)
    target_link_libraries(test_ILPColoring LINK_PUBLIC ${LIBS})
    install(TARGETS test_ILPColoring DESTINATION test/algorithms)

    add_executable(test_MISColoring test_MISColoring.cpp)
    target_link_libraries(test_MISColoring LINK_PUBLIC ${LIBS})
    install(TARGETS test_MISColoring DESTINATION test/algorithms)
endif(GUROBI_FOUND)

install(DIRECTORY benchmarks DESTINATION test/algorithms)
