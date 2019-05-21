include_directories(
    ${PROJECT_SOURCE_DIR}
    )
add_library(programoptions ProgramOptions.cpp)
install(TARGETS programoptions DESTINATION lib)

file(GLOB SOURCES
    *.h
    )
install(FILES ${SOURCES} DESTINATION include/limbo/programoptions)
