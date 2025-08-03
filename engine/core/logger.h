#pragma once

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#define LOG_INFO_ENABLED 1

#if defined(BUILD_RELEASE)
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

enum log_level {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 0,
  LOG_LEVEL_WARN = 0,
  LOG_LEVEL_INFO = 0,
  LOG_LEVEL_TRACE = 0,
  LOG_LEVEL_DEBUG = 0,
};

bool initialize_logging();
void shutdown_logging();

// Internal API logging function
EXPORT void log_output(log_level level, const char *message, ...);

// Fatal level caller
#define FALTAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#define ERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

// Custom logging
#if LOG_WARN_ENABLED
#define WARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define WARN(message, ...)
#endif

#if LOG_TRACE_ENABLED
#define TRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
#define TRACE(message, ...)
#endif

#if LOG_DEBUG_ENABLED
#define DEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define DEBUG(message, ...)
#endif

#if LOG_INFO_ENABLED
#define INFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define INFO(message, ...)
#endif
