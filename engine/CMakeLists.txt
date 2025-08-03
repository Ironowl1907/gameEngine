aux_source_directory(src SRC)
add_library(engine SHARED ${SRC})

include_directories(.)

target_include_directories(engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

