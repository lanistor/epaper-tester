#pragma once

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#  include "lvgl.h"
#else
#  include "lvgl/lvgl.h"
#endif

#include "esp_err.h"

typedef void (*esp_timer_cb_t)(void* arg);

struct esp_timer_t {
  lv_timer_t*    timer;
  esp_timer_cb_t callback;
  void*          arg;
  const char*    name;
};

typedef struct esp_timer_t* esp_timer_handle_t;

typedef enum {
  ESP_TIMER_TASK,
} esp_timer_dispatch_t;

// esp_timer_create_args_t
typedef struct {
  esp_timer_cb_t       callback;
  void*                arg;
  esp_timer_dispatch_t dispatch_method;
  const char*          name;
  bool                 skip_unhandled_events;
} esp_timer_create_args_t;

esp_err_t esp_timer_create(const esp_timer_create_args_t* create_args,
                           esp_timer_handle_t*            out_handle);

esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);

esp_err_t esp_timer_start_once(esp_timer_handle_t timer, uint64_t timeout_us);

esp_err_t esp_timer_stop(esp_timer_handle_t timer);

esp_err_t esp_timer_delete(esp_timer_handle_t timer);

// 在 project.cpp 中实现
int64_t esp_timer_get_time();
