include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

BISON_TARGET(EbeamParser
             EbeamParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/EbeamParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/EbeamParser.h
             )
FLEX_TARGET(EbeamLexer
            EbeamScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/EbeamScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(EbeamLexer EbeamParser)

file(GLOB SOURCES
    *.cc
    )
add_library(ebeamparser ${SOURCES} ${BISON_EbeamParser_OUTPUTS} ${FLEX_EbeamLexer_OUTPUTS})

install(TARGETS ebeamparser DESTINATION lib)
install(FILES EbeamDataBase.h EbeamDriver.h DESTINATION include/limbo/parsers/ebeam/bison)
