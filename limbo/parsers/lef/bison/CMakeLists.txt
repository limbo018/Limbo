include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_INCLUDE_DIRS}
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
    LefDataBase.cc    lefiDebug.cc      lefiMisc.cc       lefiPropType.cc   lefiVia.cc
    LefDriver.cc      lefiArray.cc      lefiLayer.cc      lefiNonDefault.cc lefiUnits.cc      lefiViaRule.cc
    lefiCrossTalk.cc  lefiMacro.cc      lefiProp.cc       lefiUtil.cc
    )
add_library(lefparser ${SOURCES} ${BISON_LefParser_OUTPUTS} ${FLEX_LefLexer_OUTPUTS})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(lefparser PRIVATE DEBUG_LEFPARSER)
endif()

file(GLOB HEADERS
    *.hpp
    )
if(INSTALL_LIMBO)
    install(TARGETS lefparser DESTINATION lib)
    install(FILES LefDataBase.h LefDriver.h ${HEADERS} DESTINATION include/limbo/parsers/lef/bison)
endif(INSTALL_LIMBO)
