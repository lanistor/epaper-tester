#pragma once
#include "fl_utils.h"

enum esp_log_level_t {
  ESP_LOG_NONE, /*!< No log output */
  ESP_LOG_ERROR, /*!< Critical errors, software module can not recover on its own */
  ESP_LOG_WARN, /*!< Error conditions from which recovery measures have been taken */
  ESP_LOG_INFO, /*!< Information messages which describe normal flow of events */
  ESP_LOG_DEBUG, /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
  ESP_LOG_VERBOSE /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
};

#define LOG_COLOR_BLACK "30"
#define LOG_COLOR_RED "31"
#define LOG_COLOR_GREEN "32"
#define LOG_COLOR_BROWN "33"
#define LOG_COLOR_BLUE "34"
#define LOG_COLOR_PURPLE "35"
#define LOG_COLOR_CYAN "36"
#define LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR) "\033[1;" COLOR "m"
#define LOG_RESET_COLOR "\033[0m"
#define LOG_COLOR_E LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V

#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#define LOG_FORMAT(letter, format) #letter " (%u) %s: " format "\n"
#define LOG_SYSTEM_TIME_FORMAT(letter, format) #letter " (%s) %s: " format "\n"

#define ESP_LOG_LEVEL(level, tag, format, ...)                                 \
  do {                                                                         \
    if (level == ESP_LOG_ERROR) {                                              \
      esp_log_write(ESP_LOG_ERROR, tag, LOG_FORMAT(E, format), 1, tag,         \
                    ##__VA_ARGS__);                                            \
    } else if (level == ESP_LOG_WARN) {                                        \
      esp_log_write(ESP_LOG_WARN, tag, LOG_FORMAT(W, format), 1, tag,          \
                    ##__VA_ARGS__);                                            \
    } else if (level == ESP_LOG_DEBUG) {                                       \
      esp_log_write(ESP_LOG_DEBUG, tag, LOG_FORMAT(D, format), 1, tag,         \
                    ##__VA_ARGS__);                                            \
    } else if (level == ESP_LOG_VERBOSE) {                                     \
      esp_log_write(ESP_LOG_VERBOSE, tag, LOG_FORMAT(V, format), 1, tag,       \
                    ##__VA_ARGS__);                                            \
    } else {                                                                   \
      esp_log_write(ESP_LOG_INFO, tag, LOG_FORMAT(I, format), 1, tag,          \
                    ##__VA_ARGS__);                                            \
    }                                                                          \
  } while (0)

#define ESP_LOG_LEVEL_LOCAL(level, tag, format, ...)                           \
  do {                                                                         \
    if (LOG_LOCAL_LEVEL >= level)                                              \
      ESP_LOG_LEVEL(level, tag, format, ##__VA_ARGS__);                        \
  } while (0)

#define ESP_LOGE(tag, format, ...)                                             \
  ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR, tag, format, ##__VA_ARGS__)
#define ESP_LOGW(tag, format, ...)                                             \
  ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN, tag, format, ##__VA_ARGS__)
#define ESP_LOGI(tag, format, ...)                                             \
  ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, tag, format, ##__VA_ARGS__)
#define ESP_LOGD(tag, format, ...)                                             \
  ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG, tag, format, ##__VA_ARGS__)
#define ESP_LOGV(tag, format, ...)                                             \
  ESP_LOG_LEVEL_LOCAL(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

void esp_log_write(esp_log_level_t level,
                   const char*     tag,
                   const char*     format,
                   ...);