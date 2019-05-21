include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
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
    *.cc
    )
add_library(lpparser ${SOURCES} ${BISON_LpParser_OUTPUTS} ${FLEX_LpLexer_OUTPUTS})

install(TARGETS lpparser DESTINATION lib)
install(FILES LpDataBase.h LpDriver.h DESTINATION include/limbo/parsers/lp/bison)
