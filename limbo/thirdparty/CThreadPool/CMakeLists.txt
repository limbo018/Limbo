project(CThreadPool)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(thpool STATIC ${CMAKE_CURRENT_SOURCE_DIR}/thpool.c)
add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/example.c)
target_link_libraries(example thpool ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS thpool DESTINATION lib)
install(TARGETS example DESTINATION bin/thirdparty/CThreadPool)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/thpool.h DESTINATION include/limbo/thirdparty/CThreadPool)
