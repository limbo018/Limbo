project(dlx)

file(GLOB SOURCES 
    "src/*.cpp"
    )

if(Boost_INCLUDE_DIRS)
    set(INCLUDES ${Boost_INCLUDE_DIRS})
    set(LIBS ${Boost_LIBRARIES})
else(Boost_INCLUDE_DIRS)
    set(LIBS Boost::boost)
endif(Boost_INCLUDE_DIRS)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../.. 
    ${INCLUDES}
    )
add_library(${PROJECT_NAME} STATIC ${SOURCES})

if(LIBS)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
endif(LIBS)

if(INSTALL_LIMBO)
    install(TARGETS ${PROJECT_NAME} DESTINATION lib)
    install(DIRECTORY include/dlx DESTINATION include/limbo/thirdparty)
endif(INSTALL_LIMBO)
