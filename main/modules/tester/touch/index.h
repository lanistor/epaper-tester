#pragma once

#include "basic.h"
#include "components.h"

// 触摸测试页面
class touch_test_page : public fl_widget {
 public:
  touch_test_page() : fl_widget("touch_test_page") {}
  virtual lv_obj_t* create_widget();
  virtual void      create_children();
};

// 按钮
class touch_test_button : public fl_widget {
 public:
  touch_test_button(lv_coord_t x, lv_coord_t y)
    : fl_widget("touch_test_button"), x(x), y(y) {}
  virtual lv_obj_t* create_widget();

 private:
  lv_coord_t x = 0;
  lv_coord_t y = 0;
};

// 展示点击区域的面板
class touch_show_panel : public fl_widget {
 public:
  touch_show_panel() : fl_widget("touch_show_panel") {}
  virtual lv_obj_t* create_widget();
  virtual void      create_children();

 public:
  lv_coord_t click_x = -1;
  lv_coord_t click_y = -1;
};
