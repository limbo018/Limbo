include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

BISON_TARGET(DefParser
             DefParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/DefParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/DefParser.h
             )
FLEX_TARGET(DefLexer
            DefScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/DefScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(DefLexer DefParser)

file(GLOB SOURCES
    *.cc
    )
add_library(defparser ${SOURCES} ${BISON_DefParser_OUTPUTS} ${FLEX_DefLexer_OUTPUTS})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(defparser PRIVATE DEBUG_DEFPARSER)
endif()

if(INSTALL_LIMBO)
    install(TARGETS defparser DESTINATION lib)
    install(FILES DefDataBase.h DefDriver.h DESTINATION include/limbo/parsers/def/bison)
endif(INSTALL_LIMBO)
