project(dlx)

file(GLOB SOURCES 
    "src/*.cpp"
    )

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.. 
    ${Boost_INCLUDE_DIRS} 
    )
add_library(${PROJECT_NAME} STATIC ${SOURCES})

if(INSTALL_LIMBO)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib)
    install(DIRECTORY include/dlx DESTINATION include/limbo/thirdparty)
endif(INSTALL_LIMBO)
