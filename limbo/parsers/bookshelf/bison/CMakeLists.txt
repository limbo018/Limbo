include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

BISON_TARGET(BookshelfParser
             BookshelfParser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/BookshelfParser.cc
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/BookshelfParser.h
             )
FLEX_TARGET(BookshelfLexer
            BookshelfScanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/BookshelfScanner.cc)
ADD_FLEX_BISON_DEPENDENCY(BookshelfLexer BookshelfParser)

file(GLOB SOURCES
    *.cc
    )
add_library(bookshelfparser ${SOURCES} ${BISON_BookshelfParser_OUTPUTS} ${FLEX_BookshelfLexer_OUTPUTS})

install(TARGETS bookshelfparser DESTINATION lib)
install(FILES BookshelfDataBase.h BookshelfDriver.h DESTINATION include/limbo/parsers/bookshelf/bison)
