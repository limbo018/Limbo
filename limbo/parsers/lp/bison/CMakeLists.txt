include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_INCLUDE_DIRS}
    )

BISON_TARGET(LpParser
             LpParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/LpParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/LpParser.h
             )
FLEX_TARGET(LpLexer
            LpScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/LpScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(LpLexer LpParser)

file(GLOB SOURCES
    LpDriver.cc
    )
add_library(lpparser ${SOURCES} ${BISON_LpParser_OUTPUTS} ${FLEX_LpLexer_OUTPUTS})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(lpparser PRIVATE DEBUG_LPPARSER)
endif()

if(INSTALL_LIMBO)
    install(TARGETS lpparser DESTINATION lib)
    install(FILES LpDataBase.h LpDriver.h DESTINATION include/limbo/parsers/lp/bison)
endif(INSTALL_LIMBO)
