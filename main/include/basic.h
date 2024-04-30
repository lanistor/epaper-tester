#pragma once

#define DEBUG 0

#define BATTERY_DEBUG 0

#define ENABLE_GUI_TASK_PM 0

#define RENDER_MONOCHROME 1

#define LV_TICK_PERIOD_MS 1

#include "sdkconfig.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "font/lv_font.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "epd_driver.h"
#include "epdiy_epaper.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_freertos_hooks.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "lvgl_helpers.h"

#define TAG "FlickerList"

#define FL_COLOR_WHITE LV_COLOR_MAKE(0xff, 0xff, 0xff)
#define FL_COLOR_BLACK LV_COLOR_MAKE(0x00, 0x00, 0x00)

class fl_event_bus;

extern lv_style_t fl_style_font;
extern lv_style_t lv_cont_default_style;

extern lv_disp_drv_t disp_drv;

extern esp_timer_handle_t lvgl_tick_periodic_timer;

enum class page_names : int32_t
{
  touch_test,
};
enum class event_keys : int32_t
{
  tester,
};
