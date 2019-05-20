project(def)

set(DEF_SOURCES 
    def/defiComponent.cpp
    def/defiIOTiming.cpp
    def/defiPath.cpp
    def/defiRegion.cpp
    def/defiTimingDisable.cpp
    def/defrReader.cpp
    def/def_keywords.cpp
    def/defiDebug.cpp
    def/defiMisc.cpp
    def/defiPinCap.cpp
    def/defiRowTrack.cpp
    def/defiUtil.cpp
    def/defrSettings.cpp
    def/defiAlias.cpp
    def/defiFPC.cpp
    def/defiNet.cpp
    def/defiPinProp.cpp
    def/defiScanchain.cpp
    def/defiVia.cpp
    def/defwWriter.cpp
    def/defiAssertion.cpp
    def/defiFill.cpp
    def/defiNonDefault.cpp
    def/defiProp.cpp
    def/defiSite.cpp
    def/defrCallbacks.cpp
    def/defwWriterCalls.cpp
    def/defiBlockage.cpp
    def/defiGroup.cpp
    def/defiPartition.cpp
    def/defiPropType.cpp
    def/defiSlot.cpp
    def/defrData.cpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/def
    ${CMAKE_CURRENT_SOURCE_DIR}/cdef
    ${CMAKE_CURRENT_SOURCE_DIR}/defzlib
    ${CMAKE_CURRENT_SOURCE_DIR}/cdefzlib
    ${CMAKE_CURRENT_SOURCE_DIR}/defrw
    ${CMAKE_CURRENT_SOURCE_DIR}/defdiff
    ${CMAKE_CURRENT_SOURCE_DIR}/defwrite
    ${CMAKE_CURRENT_BINARY_DIR}
    )
BISON_TARGET(DefParser def/def.y ${CMAKE_CURRENT_BINARY_DIR}/def.tab.cpp 
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/def.tab.h
             COMPILE_FLAGS "-v -pdefyy"
             )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(def STATIC ${DEF_SOURCES} ${BISON_DefParser_OUTPUTS})
install(TARGETS def DESTINATION lib)

set(CDEF_SOURCES 
    cdef/xdefiAssertion.cpp
    cdef/xdefiFPC.cpp
    cdef/xdefiMisc.cpp
    cdef/xdefiPath.cpp
    cdef/xdefiPropType.cpp
    cdef/xdefiSite.cpp
    cdef/xdefrReader.cpp
    cdef/xdefiBlockage.cpp
    cdef/xdefiFill.cpp
    cdef/xdefiNet.cpp
    cdef/xdefiPinCap.cpp
    cdef/xdefiRegion.cpp
    cdef/xdefiSlot.cpp
    cdef/xdefwWriter.cpp
    cdef/xdefiComponent.cpp
    cdef/xdefiGroup.cpp
    cdef/xdefiNonDefault.cpp
    cdef/xdefiPinProp.cpp
    cdef/xdefiRowTrack.cpp
    cdef/xdefiTimingDisable.cpp
    cdef/xdefwWriterCalls.cpp
    cdef/xdefiDebug.cpp
    cdef/xdefiIOTiming.cpp
    cdef/xdefiPartition.cpp
    cdef/xdefiProp.cpp
    cdef/xdefiScanchain.cpp
    cdef/xdefiVia.cpp
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(cdef STATIC ${CDEF_SOURCES})
install(TARGETS cdef DESTINATION lib)

set(DEFZLIB_SOURCES 
    defzlib/defzlib.cpp
    )

add_library(defzlib STATIC ${DEFZLIB_SOURCES})
install(TARGETS defzlib DESTINATION lib)

set(CDEFZLIB_SOURCES 
    cdefzlib/cdefzlib.c
    )

add_library(cdefzlib STATIC ${CDEFZLIB_SOURCES})
install(TARGETS cdefzlib DESTINATION lib)

set(DEFRW_SOURCES 
    defrw/defrw.cpp
    )

add_executable(defrw ${DEFRW_SOURCES})
target_link_libraries(defrw def ${ZLIB_LIBRARIES})
install(TARGETS defrw DESTINATION bin/thirdparty/defdef/5.8/def)

set(DEFDIFF_SOURCES 
    defdiff/diffDefRW.cpp
    defdiff/differDef.cpp
    )

add_executable(defdiff ${DEFDIFF_SOURCES})
target_link_libraries(defdiff def ${ZLIB_LIBRARIES})
install(TARGETS defdiff DESTINATION bin/thirdparty/defdef/5.8/def)

set(DEFWRITE_SOURCES 
    defwrite/defwrite.cpp
    #defwrite/defwriteCbs.cpp
    )

add_executable(defwrite ${DEFWRITE_SOURCES})
target_link_libraries(defwrite def ${ZLIB_LIBRARIES})
install(TARGETS defwrite DESTINATION bin/thirdparty/defdef/5.8/def)
