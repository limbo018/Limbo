include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

file(GLOB SOURCES
    *.cc
    )
include_directories(
    ${PROJECT_SOURCE_DIR}
    )
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(defparseradapt_uncombined STATIC ${SOURCES})
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    target_compile_definitions(defparseradapt_uncombined PRIVATE DEBUG_DEFPARSER)
endif()
set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/libdefparseradapt.a")
# merge two static libraries 
add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ar -x $<TARGET_FILE:def> 
    COMMAND ar -x $<TARGET_FILE:defparseradapt_uncombined> 
    COMMAND ar -qc libdefparseradapt.a *.o
    DEPENDS def defparseradapt_uncombined
    )
add_custom_target(defparseradapt ALL 
  DEPENDS ${OUTPUT} def)

if(INSTALL_LIMBO)
    install(FILES ${OUTPUT} DESTINATION lib)
    install(FILES DefDataBase.h DefDriver.h DESTINATION include/limbo/parsers/def/adapt)
endif(INSTALL_LIMBO)
