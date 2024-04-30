#include "../tester/simple_page/index.h"
#include "components.h"
#include "epd_driver.h"
#include "fl_icon.h"
#include "index.h"

// 入口组件
lv_obj_t* root_widget::create_widget() {
  lv_obj_t* view = create_fl_flex_obj(par, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_size(view, lv_pct(100), lv_pct(100));
  return view;
}

void root_widget::create_children() {

  // 简单的文字测试页面
  create_fl_widget(new tester_simple_page(), view);
  return;
}

void root_widget::after_create_widget() {
  this->after_update_widget();
}
