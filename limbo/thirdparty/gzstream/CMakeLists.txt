project(gzstream)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/gzstream.C)

if(INSTALL_LIMBO)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/gzstream.h DESTINATION include/limbo/thirdparty/${PROJECT_NAME})
endif(INSTALL_LIMBO)
