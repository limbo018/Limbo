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
set(DEF_HEADERS 
    def/defiAlias.hpp      def/defiDebug.hpp  def/defiGroup.hpp     def/defiNet.hpp         def/defiPinCap.hpp    def/defiRegion.hpp     def/defiSlot.hpp           def/defiVia.hpp        def/defrSettings.hpp
    def/defiAssertion.hpp  def/defiDefs.hpp   def/defiIOTiming.hpp  def/defiNonDefault.hpp  def/defiPinProp.hpp   def/defiRowTrack.hpp   def/defiTimingDisable.hpp  def/defrCallBacks.hpp  def/defwWriterCalls.hpp
    def/defiBlockage.hpp   def/defiFill.hpp   def/defiKRDefs.hpp    def/defiPartition.hpp   def/defiProp.hpp      def/defiScanchain.hpp  def/defiUser.hpp           def/defrData.hpp       def/defwWriter.hpp
    def/defiComponent.hpp  def/defiFPC.hpp    def/defiMisc.hpp      def/defiPath.hpp        def/defiPropType.hpp  def/defiSite.hpp       def/defiUtil.hpp           def/defrReader.hpp
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
if(INSTALL_LIMBO)
    install(TARGETS def DESTINATION lib)
    install(FILES ${DEF_HEADERS} DESTINATION include/limbo/thirdparty/lefdef/5.8/def/def)
endif(INSTALL_LIMBO)

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
if(INSTALL_LIMBO)
    install(TARGETS cdef DESTINATION lib)
endif(INSTALL_LIMBO)

set(DEFZLIB_SOURCES 
    defzlib/defzlib.cpp
    )

add_library(defzlib STATIC ${DEFZLIB_SOURCES})
if(INSTALL_LIMBO)
    install(TARGETS defzlib DESTINATION lib)
endif(INSTALL_LIMBO)

set(CDEFZLIB_SOURCES 
    cdefzlib/cdefzlib.c
    )

add_library(cdefzlib STATIC ${CDEFZLIB_SOURCES})
if(INSTALL_LIMBO)
    install(TARGETS cdefzlib DESTINATION lib)
endif(INSTALL_LIMBO)

set(DEFRW_SOURCES 
    defrw/defrw.cpp
    )

add_executable(defrw ${DEFRW_SOURCES})
target_link_libraries(defrw def ${ZLIB_LIBRARIES})
set_target_properties(defrw PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS defrw DESTINATION bin/thirdparty/lefdef/5.8/def)
endif(INSTALL_LIMBO)

set(DEFDIFF_SOURCES 
    defdiff/diffDefRW.cpp
    defdiff/differDef.cpp
    )

add_executable(defdiff ${DEFDIFF_SOURCES})
target_link_libraries(defdiff def ${ZLIB_LIBRARIES})
set_target_properties(defdiff PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS defdiff DESTINATION bin/thirdparty/lefdef/5.8/def)
endif(INSTALL_LIMBO)

set(DEFWRITE_SOURCES 
    defwrite/defwrite.cpp
    #defwrite/defwriteCbs.cpp
    )

add_executable(defwrite ${DEFWRITE_SOURCES})
target_link_libraries(defwrite def ${ZLIB_LIBRARIES})
set_target_properties(defwrite PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(INSTALL_LIMBO)
    install(TARGETS defwrite DESTINATION bin/thirdparty/lefdef/5.8/def)
endif(INSTALL_LIMBO)
