project(lef)

set(LEF_SOURCES 
    lef/crypt.cpp
    lef/lefiArray.cpp
    lef/lefiEncryptInt.cpp
    lef/lefiMisc.cpp
    lef/lefiPropType.cpp
    lef/lefiVia.cpp
    lef/lefrData.cpp
    lef/lefwWriter.cpp
    lef/lefiCrossTalk.cpp
    lef/lefiLayer.cpp
    lef/lefiNonDefault.cpp
    lef/lefiTBExt.cpp
    lef/lefiViaRule.cpp
    lef/lefrReader.cpp
    lef/lefwWriterCalls.cpp
    lef/lef_keywords.cpp
    lef/lefiDebug.cpp
    lef/lefiMacro.cpp
    lef/lefiProp.cpp
    lef/lefiUnits.cpp
    lef/lefrCallbacks.cpp
    lef/lefrSettings.cpp
    )
set(LEF_HEADERS
    lef/crypt.hpp      lef/lefiCrossTalk.hpp  lef/lefiDefs.hpp        lef/lefiKRDefs.hpp  lef/lefiMacro.hpp  lef/lefiNonDefault.hpp  lef/lefiPropType.hpp  lef/lefiUser.hpp  lef/lefiVia.hpp      lef/lefrCallBacks.hpp  lef/lefrReader.hpp    lef/lefwWriterCalls.hpp
    lef/lefiArray.hpp  lef/lefiDebug.hpp      lef/lefiEncryptInt.hpp  lef/lefiLayer.hpp   lef/lefiMisc.hpp   lef/lefiProp.hpp        lef/lefiUnits.hpp     lef/lefiUtil.hpp  lef/lefiViaRule.hpp  lef/lefrData.hpp       lef/lefrSettings.hpp  lef/lefwWriter.hpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lef
    ${CMAKE_CURRENT_SOURCE_DIR}/clef
    ${CMAKE_CURRENT_SOURCE_DIR}/lefzlib
    ${CMAKE_CURRENT_SOURCE_DIR}/clefzlib
    ${CMAKE_CURRENT_SOURCE_DIR}/lefrw
    ${CMAKE_CURRENT_SOURCE_DIR}/lefdiff
    ${CMAKE_CURRENT_SOURCE_DIR}/lefwrite
    ${CMAKE_CURRENT_BINARY_DIR}
    )
BISON_TARGET(LefParser lef/lef.y ${CMAKE_CURRENT_BINARY_DIR}/lef.tab.cpp 
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lef.tab.h
             COMPILE_FLAGS "-v -plefyy"
             )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(lef STATIC ${LEF_SOURCES} ${BISON_LefParser_OUTPUTS})
if(INSTALL_LIMBO)
    install(TARGETS lef DESTINATION lib)
    install(FILES ${LEF_HEADERS} DESTINATION include/limbo/thirdparty/lefdef/5.8/lef/lef)
endif(INSTALL_LIMBO)

set(CLEF_SOURCES 
    clef/xlefiArray.cpp
    clef/xlefiDebug.cpp
    clef/xlefiLayer.cpp
    clef/xlefiMisc.cpp
    clef/xlefiProp.cpp
    clef/xlefiUnits.cpp
    clef/xlefiVia.cpp
    clef/xlefrReader.cpp
    clef/xlefwWriterCalls.cpp
    clef/xlefiCrossTalk.cpp
    clef/xlefiEncryptInt.cpp
    clef/xlefiMacro.cpp
    clef/xlefiNonDefault.cpp
    clef/xlefiPropType.cpp
    clef/xlefiUtil.cpp
    clef/xlefiViaRule.cpp
    clef/xlefwWriter.cpp
    )

add_library(clef STATIC ${CLEF_SOURCES})
if(INSTALL_LIMBO)
    install(TARGETS clef DESTINATION lib)
endif(INSTALL_LIMBO)

set(LEFZLIB_SOURCES 
    lefzlib/lefzlib.cpp
    )

add_library(lefzlib STATIC ${LEFZLIB_SOURCES})
if(INSTALL_LIMBO)
    install(TARGETS lefzlib DESTINATION lib)
endif(INSTALL_LIMBO)

set(CLEFZLIB_SOURCES 
    clefzlib/clefzlib.c
    )

add_library(clefzlib STATIC ${CLEFZLIB_SOURCES})
if(INSTALL_LIMBO)
    install(TARGETS clefzlib DESTINATION lib)
endif(INSTALL_LIMBO)

set(LEFRW_SOURCES 
    lefrw/lefrw.cpp
    )

add_executable(lefrw ${LEFRW_SOURCES})
target_link_libraries(lefrw lef ${ZLIB_LIBRARIES})
set_target_properties(lefrw PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS lefrw DESTINATION bin/thirdparty/lefdef/5.8/lef)
endif(INSTALL_LIMBO)

set(LEFDIFF_SOURCES 
    lefdiff/diffLefRW.cpp
    lefdiff/differLef.cpp
    )

add_executable(lefdiff ${LEFDIFF_SOURCES})
target_link_libraries(lefdiff lef ${ZLIB_LIBRARIES})
set_target_properties(lefdiff PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS lefdiff DESTINATION bin/thirdparty/lefdef/5.8/lef)
endif(INSTALL_LIMBO)

set(LEFWRITE_SOURCES 
    lefwrite/lefwrite.cpp
    #lefwrite/lefwriteCbs.cpp
    )

add_executable(lefwrite ${LEFWRITE_SOURCES})
target_link_libraries(lefwrite lef ${ZLIB_LIBRARIES})
set_target_properties(lefwrite PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS lefwrite DESTINATION bin/thirdparty/lefdef/5.8/lef)
endif(INSTALL_LIMBO)
