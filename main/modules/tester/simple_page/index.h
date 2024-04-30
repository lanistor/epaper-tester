#pragma once

#include "components.h"
#include <string>

// 简单测试页面，只展示简单的文字
class tester_simple_page : public fl_widget {
 public:
  tester_simple_page() : fl_widget("tester_simple_page") {}
  virtual lv_obj_t* create_widget();
  virtual void      create_children();
};
