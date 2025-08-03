#include "core/logger.h"
#include "defines.h"

EXPORT void sayHello(void) { WARN("This is a warning with: {}", 45); }
