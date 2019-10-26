include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_INCLUDE_DIRS}
    )

BISON_TARGET(GdfParser
             GdfParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/GdfParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/GdfParser.h
             )
FLEX_TARGET(GdfLexer
            GdfScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/GdfScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(GdfLexer GdfParser)

file(GLOB SOURCES
    GdfDriver.cc
    )
add_library(gdfparser ${SOURCES} ${BISON_GdfParser_OUTPUTS} ${FLEX_GdfLexer_OUTPUTS})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(gdfparser PRIVATE DEBUG_GDFPARSER)
endif()

if(INSTALL_LIMBO)
    install(TARGETS gdfparser DESTINATION lib)
    install(FILES GdfDataBase.h GdfDriver.h DESTINATION include/limbo/parsers/gdf/bison)
endif(INSTALL_LIMBO)
