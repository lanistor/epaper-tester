#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "fl_async.h"

#define FL_ASYNC_HD_TAG "FL_ASYNC_HARDWARE"

// 回调入口
static void _async_hardware_cb(void* arg) {
  auto arg_model = (fl_async_arg_model*)arg;

  auto cb       = arg_model->cb;
  auto real_arg = arg_model->arg;
  auto xHandle  = arg_model->xHandle;

  delete arg_model;

  cb(real_arg);

  if (xHandle) {
    vTaskDelete(xHandle);
  }
}

// fl_delay 回调
static void _timer_cb(void* arg) {
  auto arg_model = (fl_timer_arg_model*)arg;

  auto cb       = arg_model->cb;
  auto real_arg = arg_model->arg;
  auto once     = arg_model->once;

  if (once) {
    delete arg_model;
  }
  cb(real_arg);
}

// 异步执行，基于硬件任务管理，执行延迟比 `lv_async_call` 低
void fl_thread_task(fl_async_cb            cb,
                    void*                  data,
                    string                 name,
                    int                    core,
                    unsigned int           stack_size,
                    unsigned portBASE_TYPE priority) {
  auto arg = new fl_async_arg_model(cb, data, name);

  auto res =
    xTaskCreatePinnedToCore(&_async_hardware_cb, name.c_str(), stack_size, arg,
                            priority, &arg->xHandle, core);

  if (res != pdPASS) {
    ESP_LOGE(FL_ASYNC_HD_TAG,
             "fl_thread_task. name: %s; "
             "res: %d;  core: %d; priority: %d; stack size: %d; ",
             name.c_str(), res, core, priority, stack_size);

    // 失败后也要保证回调函数能执行，否则会出现内存泄露
    arg->xHandle = NULL;
    _async_hardware_cb(arg);
  }
}

/**
 * @brief 硬件延迟触发，使用 esp_timer 实现
 */
esp_timer_handle_t fl_timer_delay(fl_async_cb cb,
                                  int         ms,
                                  void*       data,
                                  string      name,
                                  bool        skip_unhandled_events) {
  assert(ms <= 60 * 1000);  // fl_delay 延时不能超过60s
  auto arg = new fl_timer_arg_model(cb, data, true, false, name);

  esp_timer_create_args_t timer_args = {
    .callback              = &_timer_cb,
    .arg                   = arg,
    .name                  = name.c_str(),
    .skip_unhandled_events = skip_unhandled_events,
  };
  esp_timer_handle_t timer_handler;
  ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handler));
  ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, (uint64_t)ms * 1000));
  return timer_handler;
}

/**
 * @brief 清除延时，仅用于 fl_timer_delay 创建的定时器
 * 
 */
void fl_timer_del(esp_timer_handle_t handler) {
  if (!handler) {
    return;
  }

  ESP_ERROR_CHECK(esp_timer_delete(handler));
}
