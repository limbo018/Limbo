include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ZLIB_INCLUDE_DIRS}
    )

file(GLOB SOURCES
    *.cpp
    )
file(GLOB HEADERS
    *.h
    )
add_library(gdsparser STATIC ${SOURCES})
target_compile_options(gdsparser PRIVATE "-DZLIB=1")
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(gdsparser PRIVATE DEBUG_GDSREADER DEBUG_GDSWRITER)
endif()

if(INSTALL_LIMBO)
    install(TARGETS gdsparser DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include/limbo/parsers/gdsii/stream)
endif(INSTALL_LIMBO)
