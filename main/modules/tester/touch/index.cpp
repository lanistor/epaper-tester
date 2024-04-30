#include "./index.h"
#include "fl_utils.h"

// touch_test_page
lv_obj_t* touch_test_page::create_widget() {
  lv_obj_t* view = create_fl_lv_obj(par);
  lv_obj_set_size(view, lv_pct(100), lv_pct(100));
  return view;
}

void touch_test_page::create_children() {
  // 画一些点
  static lv_coord_t xs[6] = {10, 200, 400, 600, 800, 1004};
  static lv_coord_t ys[7] = {10, 190, 370, 550, 640, 690, 738};
  for (int32_t y_ind = 0; y_ind < 7; y_ind++) {
    for (int32_t x_ind = 0; x_ind < 6; x_ind++) {
      create_fl_widget(new touch_test_button(xs[x_ind], ys[y_ind]), view);
    }
  }

  // 点击接收面板
  create_fl_widget(new touch_show_panel(), view);
}

// touch_test_button
lv_obj_t* touch_test_button::create_widget() {
  auto label = create_fl_label(par, false);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_pos(label, x, y);
  lv_label_set_text(label, "+");
  return label;
}

// touch_show_panel
static void _panel_click_cb(lv_event_t* e) {
  auto info       = lv_event_get_indev(e);
  auto target     = (touch_show_panel*)e->user_data;
  auto last_point = info->proc.types.pointer.last_point;
  target->click_x = last_point.x;
  target->click_y = last_point.y;
  target->update_widget();
}

lv_obj_t* touch_show_panel::create_widget() {
  lv_obj_t* view = create_fl_lv_obj(par);
  lv_obj_set_size(view, lv_pct(100), lv_pct(100));
  lv_obj_set_pos(view, 0, 0);
  lv_obj_set_style_bg_opa(view, 0, LV_PART_MAIN);
  lv_obj_add_event_cb(view, _panel_click_cb, LV_EVENT_CLICKED, this);
  return view;
}

void touch_show_panel::create_children() {
  if (click_x < 0 || click_y < 0) {
    return;
  }
  static lv_coord_t point_width = 10;
  auto              point       = create_fl_lv_obj(view);
  lv_obj_set_size(point, point_width, point_width);
  lv_obj_set_style_bg_color(point, color_make(0x00), LV_PART_MAIN);
  lv_obj_set_pos(point, click_x - point_width / 2, click_y - point_width / 2);
}
