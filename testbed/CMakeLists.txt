project(Testbed VERSION 1.0.0 LANGUAGES C CXX)

# Testbed source files
set(TESTBED_SOURCES
    src/test.cpp
)

# Create the testbed executable
add_executable(${PROJECT_NAME} ${TESTBED_SOURCES})

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "testbed"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link to the engine library
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GameEngine::Engine
        Threads::Threads
)

# Compiler definitions
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:TESTBED_DEBUG>
        $<$<CONFIG:Release>:TESTBED_RELEASE>
)

# Platform-specific settings
if(WIN32)
  # Windows-specific settings
  set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
elseif(APPLE)
  # macOS-specific settings
  set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE FALSE
    )
endif()

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Copy engine library to output directory on Windows
if(WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GameEngine::Engine>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
