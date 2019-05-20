project(dlx)

file(GLOB SOURCES 
    "src/*.cpp"
    )

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.. 
    ${Boost_INCLUDE_DIRS} 
    )
add_library(${PROJECT_NAME} STATIC ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/dlx DESTINATION include/thirdparty)
