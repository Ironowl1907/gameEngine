cmake_minimum_required(VERSION 3.16)

# Project configuration
project(GameEngine
    VERSION 1.0.0
    DESCRIPTION "Game Engine Project"
    LANGUAGES C CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Global compiler flags
if(MSVC)
  add_compile_options(/W4)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
    add_compile_definitions(DEBUG)
  else()
    add_compile_options(-O3)
    add_compile_definitions(NDEBUG)
  endif()
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable compile_commands.json for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform-specific settings
if(WIN32)
  add_compile_definitions(PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
  add_compile_definitions(PLATFORM_LINUX)
elseif(APPLE)
  add_compile_definitions(PLATFORM_MACOS)
endif()

# Find required packages
find_package(Threads REQUIRED)

# Add subdirectories
add_subdirectory(engine)
add_subdirectory(testbed)
# add_subdirectory(editor)
# add_subdirectory(runtime)

# Optional: Add custom targets for documentation, packaging, etc.
add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMENT "Cleaning all build artifacts"
)

