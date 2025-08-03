#include <core/logger.h>

int main(void) {
  // Initialize logging (handle the bool return value)
  if (!Logger::initialize_logging()) {
    printf("Failed to initialize logging!\n");
    return -1;
  }

  WARN("THIS IS A WARNING WITH A CODE: %d", 45);

  INFO("This is an info message with number: %d", 123);
  ERROR("This is an error message");
  DEBUG("Debug message with string: %s", "hello world");
  TRACE("Trace message");
  FATAL("Fatal message - this is critical!");

  // Shutdown logging
  Logger::shutdown_logging();

  return 0;
}
