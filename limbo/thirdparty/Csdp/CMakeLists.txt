project(Csdp)

include_directories(
    include 
    lib 
    solver 
    test 
    theta 
    example 
    )

set(CSDP_SOURCES
    lib/add_mat.c
    lib/calc_pobj.c
    lib/Fnorm.c
    lib/linesearch.c
    lib/mat_multsp.c
    lib/op_at.c
    lib/qreig.c
    lib/solvesys.c
    lib/tweakgap.c
    lib/zero_mat.c
    lib/addscaledmat.c
    lib/chol.c
    lib/freeprob.c
    lib/makefill.c
    lib/matvec.c
    lib/op_o.c
    lib/readprob.c
    lib/sortentries.c
    lib/user_exit.c
    lib/allocmat.c
    lib/copy_mat.c
    lib/initparams.c
    lib/make_i.c
    lib/norms.c
    lib/packed.c
    lib/readsol.c
    lib/sym_mat.c
    lib/writeprob.c
    lib/calc_dobj.c
    lib/easysdp.c
    lib/initsoln.c
    lib/mat_mult.c
    lib/op_a.c
    lib/psd_feas.c
    lib/sdp.c
    lib/trace_prod.c
    lib/writesol.c
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# must be added to avoid using unsigned shorts 
set(CSDP_COMPILE_DEFINITIONS NOSHORTS)

add_library(sdp STATIC ${CSDP_SOURCES})
target_compile_definitions(sdp PRIVATE ${CSDP_COMPILE_DEFINITIONS})
if(INSTALL_LIMBO)
    install(TARGETS sdp DESTINATION lib)
endif(INSTALL_LIMBO)

set(LIBS sdp ${OpenBLAS_LIBNAME} m ${CMAKE_THREAD_LIBS_INIT} gfortran)
if(UNIX AND NOT APPLE)
    set(LIBS ${LIBS} rt)
endif()

add_executable(csdp solver/csdp.c)
target_compile_definitions(csdp PRIVATE ${CSDP_COMPILE_DEFINITIONS})
add_executable(csdp_test solver/csdp_test.c)
target_compile_definitions(csdp_test PRIVATE ${CSDP_COMPILE_DEFINITIONS})
target_link_libraries(csdp ${LIBS})
target_link_libraries(csdp_test ${LIBS})
set_target_properties(csdp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set_target_properties(csdp_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS csdp csdp_test DESTINATION bin/thirdparty/Csdp/solver)
endif(INSTALL_LIMBO)

add_executable(complement theta/complement.c)
target_compile_definitions(complement PRIVATE ${CSDP_COMPILE_DEFINITIONS})
add_executable(graphtoprob theta/graphtoprob.c)
target_compile_definitions(graphtoprob PRIVATE ${CSDP_COMPILE_DEFINITIONS})
add_executable(rand_graph theta/rand_graph.c)
target_compile_definitions(rand_graph PRIVATE ${CSDP_COMPILE_DEFINITIONS})
add_executable(theta theta/theta.c)
target_compile_definitions(theta PRIVATE ${CSDP_COMPILE_DEFINITIONS})
target_link_libraries(complement ${LIBS})
target_link_libraries(graphtoprob ${LIBS})
target_link_libraries(rand_graph ${LIBS})
target_link_libraries(theta ${LIBS})
set_target_properties(graphtoprob PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set_target_properties(complement PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set_target_properties(graphtoprob PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set_target_properties(rand_graph PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set_target_properties(theta PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS complement graphtoprob rand_graph theta DESTINATION bin/thirdparty/Csdp/theta)
endif(INSTALL_LIMBO)

add_executable(${PROJECT_NAME}_example example/example.c)
target_compile_definitions(${PROJECT_NAME}_example PRIVATE ${CSDP_COMPILE_DEFINITIONS})
target_link_libraries(${PROJECT_NAME}_example ${LIBS})
set_target_properties(${PROJECT_NAME}_example
        PROPERTIES OUTPUT_NAME example
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
        )
if(INSTALL_LIMBO)
    install(TARGETS ${PROJECT_NAME}_example DESTINATION bin/thirdparty/Csdp/example)
endif(INSTALL_LIMBO)

if(INSTALL_LIMBO)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION include/limbo/thirdparty/Csdp)
endif(INSTALL_LIMBO)
