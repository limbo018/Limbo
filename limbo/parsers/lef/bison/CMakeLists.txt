include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

BISON_TARGET(LefParser
             LefParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/LefParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/LefParser.h
             )
FLEX_TARGET(LefLexer
            LefScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/LefScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(LefLexer LefParser)

file(GLOB SOURCES
    *.cc
    )
add_library(lefparser ${SOURCES} ${BISON_LefParser_OUTPUTS} ${FLEX_LefLexer_OUTPUTS})

file(GLOB HEADERS
    *.hpp
    )
install(TARGETS lefparser DESTINATION lib)
install(FILES LefDataBase.h LefDriver.h ${HEADERS} DESTINATION include/limbo/parsers/lef/bison)
