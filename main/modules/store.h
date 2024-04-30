#pragma once

#include "app/models/current_date.h"
#include "app/models/index.h"
#include "basic.h"
#include "calendar/model.h"
#include "desk_calendar/model.h"
#include "device/model.h"
#include "device/wifi_clock.h"
#include "esp_heap_caps.h"
#include "group/models/index.h"
#include "list/model.h"
#include "notify/model.h"
#include "quadrant/model.h"
#include "screen_lock/model.h"
#include "setting/model.h"
#include "tomato/model.h"
#include "user/model.h"

// ui相关
struct ui_store {
  int status_bar_height      = 30;  // 状态栏高度
  int menu_cont_width        = 78;  // menu区域的宽度
  int menu_item_height       = 85;  // menu区域的宽度
  int menu_item_height_small = 65;  // 小尺寸的menu区域的宽度
  int list_date_range_bar_height = 55;  // 日历页顶部日期搜索栏的高度
};

// 全局状态模型，仅存储全局数据，如当前页面路由
class fl_store {
 public:
  page_names          current_page = page_names::list;
  device_store        device;
  wifi_store          wifi;
  clock_store         clock;  // 系统时钟
  screen_lock_store   screen_lock;
  app_store           app;
  ui_store            ui;
  user_store          user;
  fl_group_store      group;
  notify_store        notify;
  list_store          list;
  calendar_store      calendar;
  quadrant_store      quadrant;
  fl_tomato_store     tomato;
  desk_calendar_store desk_calendar;
  setting_store       setting;
  date_store          date;  // 当前日期

  // SPIRAM 申请内存
  void* operator new(size_t size, void* ptr = NULL) {
    if (ptr) {
      return ptr;
    }
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
  }

  // 登录用户
  fl_login_user& login_user() {
    return user.user;
  }

  // 是否已经登录
  bool is_logined() {
    return user.user.is_logined();
  }

  // 登录用户的ID
  string login_user_id() {
    return user.user.id;
  }

  /**
   * @brief 是否可以发起网络请求
   *   - 睡眠被唤醒时，网络异步连接，此时可以发起网络请求，因为请求中会等待网络成功
   *   - 若网络从未连接成功过，则睡眠唤醒不可能连网成功
   */
  bool able_fetch_data() {
    return !wifi.failed() && wifi.first_connected;
  }

  // 是否允许请求用户数据，要求: 联网(或联网中),
  bool able_fetch_user_data() {
    return able_fetch_data() && is_logined();
  }

  // 当前在网络设置页面
  bool in_network_setting_page() {
    return current_page == page_names::setting &&
           setting.current_page == setting_pages::network;
  }
};

// 全局状态
extern fl_store* global_store;
