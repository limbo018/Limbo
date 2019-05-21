include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
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

install(TARGETS gdsparser DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/limbo/parsers/gdsii/stream)
