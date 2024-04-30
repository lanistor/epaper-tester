#pragma once

#include "basic.h"
#include "components.h"

// 入口组件
class root_widget : public fl_widget {
 public:
  root_widget() : fl_widget("root_widget") {}

  virtual lv_obj_t* create_widget();
  virtual void      create_children();
  virtual void      after_create_widget();
};
