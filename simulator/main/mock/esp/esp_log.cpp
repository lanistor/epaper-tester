#include "esp_log.h"
#include <stdarg.h>
#include <stdio.h>

void esp_log_writev(esp_log_level_t level,
                    const char*     tag,
                    const char*     format,
                    va_list         args) {
  vprintf(format, args);
}

void esp_log_write(esp_log_level_t level,
                   const char*     tag,
                   const char*     format,
                   ...) {
  va_list list;
  va_start(list, format);
  esp_log_writev(level, tag, format, list);
  va_end(list);
}