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
add_library(lefparseradapt_uncombined STATIC ${SOURCES})
set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/liblefparseradapt.a")
# merge two static libraries 
add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ar -x $<TARGET_FILE:lef> 
    COMMAND ar -x $<TARGET_FILE:lefparseradapt_uncombined> 
    COMMAND ar -qc liblefparseradapt.a *.o
    DEPENDS lef lefparseradapt_uncombined
    )
add_custom_target(lefparseradapt ALL DEPENDS ${OUTPUT})

install(FILES ${OUTPUT} DESTINATION lib)
install(FILES LefDataBase.h LefDriver.h DESTINATION include/limbo/parsers/lef/adapt)
