#include "./project.h"
#include "./include/index.h"
#include "app_services.h"
#include "basic.h"
#include "esp_timer.h"

// 屏幕驱动
lv_disp_drv_t disp_drv;

// lvgl 心跳轮询定时器
esp_timer_handle_t lvgl_tick_periodic_timer;

// 程序开始时间，us
clock_t _start;

void flicker_demo_widgets() {
  _start = clock();

  fl_before_start();

  start_application();

  fl_after_start();
}

int64_t esp_timer_get_time() {
  return clock() - _start;
}
