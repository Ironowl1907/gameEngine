#include "logger.h"
#include <cstdarg>
#include <cstdio>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> Logger::s_logger;

bool Logger::initialize_logging() {
  try {
    s_logger = spdlog::stdout_color_mt("console");

    s_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

#if defined(BUILD_RELEASE)
    s_logger->set_level(spdlog::level::info);
#else
    s_logger->set_level(spdlog::level::trace);
#endif

    s_logger->info("Logger initialized successfully");
    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    fprintf(stderr, "Log initialization failed: %s\n", ex.what());
    return false;
  }
}

void Logger::shutdown_logging() {
  if (s_logger) {
    s_logger->info("Shutting down logger");
    s_logger->flush();
    spdlog::drop("console");
    s_logger.reset();
  }
  spdlog::shutdown();
}

void Logger::log_output(log_level level, const char *message, ...) {
  if (!s_logger) {
    fprintf(stderr, "Logger not initialized!\n");
    return;
  }

  // Handle variadic arguments
  va_list args;
  va_start(args, message);

  // Create buffer for formatted message
  char buffer[4096];
  vsnprintf(buffer, sizeof(buffer), message, args);

  va_end(args);

  // Log based on level
  switch (level) {
  case LOG_LEVEL_FATAL:
    s_logger->critical(buffer);
    s_logger->flush();
    break;
  case LOG_LEVEL_ERROR:
    s_logger->error(buffer);
    break;
  case LOG_LEVEL_WARN:
    s_logger->warn(buffer);
    break;
  case LOG_LEVEL_INFO:
    s_logger->info(buffer);
    break;
  case LOG_LEVEL_DEBUG:
    s_logger->debug(buffer);
    break;
  case LOG_LEVEL_TRACE:
    s_logger->trace(buffer);
    break;
  default:
    s_logger->info(buffer);
    break;
  }
}
