project(Engine VERSION 1.0.0 LANGUAGES C CXX)

# Add vendor libraries first
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
add_subdirectory(vendor/spdlog)

# Engine source files
set(ENGINE_SOURCES
    src/main.cpp
    src/core/logger.cpp
)

set(ENGINE_HEADERS
    src/core/logger.h
    defines.h
)

add_library(${PROJECT_NAME} SHARED
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Threads::Threads
    PRIVATE
        spdlog::spdlog
)

# Compiler definitions
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ENGINE_EXPORTS
    PUBLIC
        $<$<CONFIG:Debug>:ENGINE_DEBUG>
        $<$<CONFIG:Release>:ENGINE_RELEASE>
)

# Platform-specific linking
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
elseif(UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()

# Export symbols on Windows
if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORTS)
  set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()


# Create alias for consistent naming
add_library(GameEngine::Engine ALIAS ${PROJECT_NAME})
