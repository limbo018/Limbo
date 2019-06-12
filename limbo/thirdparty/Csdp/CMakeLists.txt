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
add_library(sdp STATIC ${CSDP_SOURCES})
install(TARGETS sdp DESTINATION lib)

set(LIBS sdp openblas m ${CMAKE_THREAD_LIBS_INIT} gfortran)
if(UNIX AND NOT APPLE)
    set(LIBS ${LIBS} rt)
endif()

add_executable(csdp solver/csdp.c)
add_executable(csdp_test solver/csdp_test.c)
target_link_libraries(csdp ${LIBS})
target_link_libraries(csdp_test ${LIBS})
install(TARGETS csdp csdp_test DESTINATION bin/thirdparty/Csdp/solver)

add_executable(complement theta/complement.c)
add_executable(graphtoprob theta/graphtoprob.c)
add_executable(rand_graph theta/rand_graph.c)
add_executable(theta theta/theta.c)
target_link_libraries(complement ${LIBS})
target_link_libraries(graphtoprob ${LIBS})
target_link_libraries(rand_graph ${LIBS})
target_link_libraries(theta ${LIBS})
install(TARGETS complement graphtoprob rand_graph theta DESTINATION bin/thirdparty/Csdp/theta)

add_executable(${PROJECT_NAME}_example example/example.c)
target_link_libraries(${PROJECT_NAME}_example ${LIBS})
set_target_properties(${PROJECT_NAME}_example
        PROPERTIES OUTPUT_NAME example)
install(TARGETS ${PROJECT_NAME}_example DESTINATION bin/thirdparty/Csdp/example)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION include/limbo/thirdparty/Csdp)
