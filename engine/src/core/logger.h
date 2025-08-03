#pragma once
#include "defines.h"
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define LOG_WARN_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#define LOG_INFO_ENABLED 1

#if defined(BUILD_RELEASE)
#undef LOG_DEBUG_ENABLED
#undef LOG_TRACE_ENABLED
#endif

class Logger {
public:
  enum log_level {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5,
  };

  EXPORT static bool initialize_logging();
  EXPORT static void shutdown_logging();

  EXPORT static void log_output(log_level level, const char *message, ...);

private:
  static std::shared_ptr<spdlog::logger> s_logger;
};

#define GET_LOGGER() Logger::get_logger()

#define FATAL(message, ...)                                                    \
  Logger::log_output(Logger::LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#define ERROR(message, ...)                                                    \
  Logger::log_output(Logger::LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

// Custom logging
#if LOG_WARN_ENABLED
#define WARN(message, ...)                                                     \
  Logger::log_output(Logger::LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define WARN(message, ...)
#endif

#if LOG_TRACE_ENABLED
#define TRACE(message, ...)                                                    \
  Logger::log_output(Logger::LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
#define TRACE(message, ...)
#endif

#if LOG_DEBUG_ENABLED
#define DEBUG(message, ...)                                                    \
  Logger::log_output(Logger::LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define DEBUG(message, ...)
#endif

#if LOG_INFO_ENABLED
#define INFO(message, ...)                                                     \
  Logger::log_output(Logger::LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define INFO(message, ...)
#endif
