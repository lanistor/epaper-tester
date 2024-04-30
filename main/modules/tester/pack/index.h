#pragma once

#include "common_model.h"
#include "components.h"

// 测试回调
typedef function<void()> test_cb_t;

// 组装时测试按钮组件，可测试蜂鸣器、触屏，并切换到用户购买首页
class pack_test_bar : public fl_widget {
 public:
  pack_test_bar() : fl_widget("pack_test_bar") {}
  virtual lv_obj_t* create_widget();
  virtual void      create_children();
  virtual void      after_create_widget();

  // 添加一个测试按钮
  lv_obj_t* add_but_item(string text, test_cb_t cb);

  // 添加跳转到该页面的按钮
  static void add_test_bar();
};

class refresh_test_service {
 private:
  fl_rect      area;
  int          count;
  fl_common_cb on_close = NULL;

 private:
  int       current_index = 0;
  lv_obj_t* frame         = nullptr;
  lv_obj_t* cont          = nullptr;

 public:
  refresh_test_service(fl_rect area, int count, fl_common_cb on_close = NULL)
    : area(area), count(count), on_close(on_close){};

 public:
  void start();
  void clear();

 private:
  void start_inner();
};
