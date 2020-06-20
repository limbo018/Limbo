project(CThreadPool)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME}_thpool STATIC ${CMAKE_CURRENT_SOURCE_DIR}/thpool.c)
add_executable(${PROJECT_NAME}_example ${CMAKE_CURRENT_SOURCE_DIR}/example.c)
target_link_libraries(${PROJECT_NAME}_example ${PROJECT_NAME}_thpool ${CMAKE_THREAD_LIBS_INIT})

if(INSTALL_LIMBO)
    install(TARGETS ${PROJECT_NAME}_thpool DESTINATION lib)
    install(TARGETS ${PROJECT_NAME}_example DESTINATION bin/thirdparty/CThreadPool)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/thpool.h DESTINATION include/limbo/thirdparty/CThreadPool)
endif(INSTALL_LIMBO)
