include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

BISON_TARGET(VerilogParser
             VerilogParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/VerilogParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/VerilogParser.h
             )
FLEX_TARGET(VerilogLexer
            VerilogScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/VerilogScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(VerilogLexer VerilogParser)

file(GLOB SOURCES
    *.cc
    )
add_library(verilogparser STATIC ${SOURCES} ${BISON_VerilogParser_OUTPUTS} ${FLEX_VerilogLexer_OUTPUTS})

install(TARGETS verilogparser DESTINATION lib)
install(FILES VerilogDataBase.h VerilogDriver.h DESTINATION include/limbo/parsers/verilog/bison)
