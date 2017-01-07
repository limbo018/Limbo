file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB SRCS_TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

add_library(programoptions STATIC ${SRCS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(test_ProgramOptions ${SRCS_TEST})
target_link_libraries(test_ProgramOptions programoptions) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
