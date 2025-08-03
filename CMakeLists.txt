cmake_minimum_required(VERSION 3.10)
project(GameEngine)

include_directories(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(engine/src SRC)

add_library(engine SHARED ${SRC})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/engine)
