include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_INCLUDE_DIRS}
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
    EbeamDriver.cc
    )
add_library(ebeamparser ${SOURCES} ${BISON_EbeamParser_OUTPUTS} ${FLEX_EbeamLexer_OUTPUTS})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(ebeamparser PRIVATE DEBUG_EBEAMPARSER)
endif()

if(INSTALL_LIMBO)
    install(TARGETS ebeamparser DESTINATION lib)
    install(FILES EbeamDataBase.h EbeamDriver.h DESTINATION include/limbo/parsers/ebeam/bison)
endif(INSTALL_LIMBO)
