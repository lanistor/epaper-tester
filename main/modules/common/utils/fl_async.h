#pragma once

#include "esp_freertos_hooks.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl/lvgl.h"
#include <functional>
#include <stdlib.h>
#include <string>

using namespace std;

// 回调函数定义
typedef function<void(void*)> fl_async_cb;  // 带参数回调


// 异步参数模型
class fl_async_arg_model {
 public:
  fl_async_cb   cb;
  void*         arg = NULL;  // 真实的参数
  string        name;
  xTaskHandle   xHandle     = NULL;

  fl_async_arg_model(fl_async_cb cb, void* arg, string name)
    : cb(cb), arg(arg), name(name) {}
};

// 定时器参数模型
class fl_timer_arg_model {
 public:
  fl_async_cb cb;
  void*       arg = NULL;  // 真实的参数
  bool        once;  // 是否只执行一次
  bool        run_on_start;  // 启动定时器时是否执行
  string      name;

  fl_timer_arg_model(fl_async_cb cb,
                     void*       arg,
                     bool        once,
                     bool        run_on_start,
                     string      name)
    : cb(cb), arg(arg), once(once), run_on_start(run_on_start), name(name) {}
};

/**
 * @brief 延迟触发，使用 esp_timer 实现
 */
esp_timer_handle_t fl_timer_delay(fl_async_cb cb,
                                  int         ms,
                                  void*       data = NULL,
                                  string      name = "fl_timer_delay__unknown",
                                  bool        skip_unhandled_events = true);

/**
 * @brief 清除延时，仅用于 fl_timer_delay 创建的定时器
 * 
 */
void fl_timer_del(esp_timer_handle_t handler);

/**
 * @brief 新开线程执行任务
 * 
 * 【使用限制】因为其栈内存是独立的，所以限制以下使用场景
 *   1. 确定回调中及后续的同步/异步操作中不会出现 lvgl 相关操作
 *   2. 确定回调中及后续的同步/异步操作中，不会占用太多栈内存
 * 
 * @param cb 回调函数
 * @param data 自定义数据
 * @param name 任务名
 * @param stack_size 栈大小，如果是http请求，可设置为更大值，以满足json解析时对栈的要求
 * @param priority 任务优先级
 */
void fl_thread_task(fl_async_cb            cb,
                    void*                  data = NULL,
                    string                 name = "fl_thread_task__unknown",
                    int                    core = 1,
                    unsigned int           stack_size = 1024 * 4,
                    unsigned portBASE_TYPE priority   = tskIDLE_PRIORITY);

/**
 * @brief 异步执行函数: 使用lvgl实现
 * 
 * 通常用于UI的异步处理，lvgl async 不支持并发，请保证只在主进程中执行，否则会偶尔引起Crash
 * 
 * @param cb 回调函数
 * @param data 自定义数据
 * @param name 任务名
 */
void fl_lvgl_async(fl_async_cb cb,
                   void*       data = NULL,
                   string      name = "fl_lvgl_async__unknown");

/**
 * @brief 线程处理安全的 fl_lvgl_async ，会在主线程中执行
 * 主线程调用时，可直接调用 fl_lvgl_async，其他线程中如果有lvgl调用，请使用此方法
 */
void fl_lvgl_safe_async(fl_async_cb cb,
                   void*       data = NULL,
                   string      name = "fl_lvgl_safe_async__unknown");

// 在主进程中安全地执行异步队列
void run_safe_async_list();

/**
 * @brief 延时触发，使用 lvgl 实现
 * 
 * 通常用于UI的延时处理处理
 * 
 * @param cb 回调函数
 * @param ms 执行间隔(毫秒)
 * @param data 自定义数据
 */
lv_timer_t* fl_lvgl_delay(fl_async_cb cb,
                          int         ms,
                          void*       data = NULL,
                          string      name = "fl_delay__unknown");

/**
 * @brief 清除定时器，仅可用于清除 fl_lvgl_delay 创建的定时器，并且清除 fl_lvgl_delay 创建的定时器时只能用此方法因为此方法会同时清空延时计时
 * 
 * 可用于 fl_delay, fl_interval
 * 
 * @param timer_value 
 */
void fl_lvgl_timer_del(lv_timer_t* timer_value);
