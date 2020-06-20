if(Boost_INCLUDE_DIRS)
    set(INCLUDES ${Boost_INCLUDE_DIRS})
    set(LIBS ${Boost_LIBRARIES})
else(Boost_INCLUDE_DIRS)
    set(LIBS Boost::boost)
endif(Boost_INCLUDE_DIRS)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDES}
    ${ZLIB_INCLUDE_DIRS}
    )

file(GLOB SOURCES
    *.cpp
    )
file(GLOB HEADERS
    *.h
    )
add_library(gdsdb STATIC ${SOURCES})
target_compile_options(gdsdb PRIVATE "-DZLIB=1")
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(gdsdb PRIVATE DEBUG_GDSREADER DEBUG_GDSWRITER)
endif()
if(LIBS)
    target_link_libraries(gdsdb PRIVATE ${LIBS})
endif(LIBS)

if(INSTALL_LIMBO)
    install(TARGETS gdsdb DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include/limbo/parsers/gdsii/gdsdb)
endif(INSTALL_LIMBO)
