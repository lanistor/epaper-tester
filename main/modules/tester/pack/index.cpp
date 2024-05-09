#include "./index.h"
#include "basic.h"
#include "common_model.h"

const char* TESTER_TAG = "TESTER";

lv_obj_t* pack_test_bar::create_widget() {
  lv_obj_t* view = create_fl_flex_obj(par, LV_FLEX_FLOW_ROW);
  lv_obj_set_size(view, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_column(view, 20, LV_PART_MAIN);
  lv_obj_set_style_pad_all(view, 20, LV_PART_MAIN);
  lv_obj_set_style_radius(view, 6, LV_PART_MAIN);

  auto bt_count = 1;
  lv_obj_set_pos(view, epd_rotated_display_width() - 20 - 150 * bt_count, 640);

  return view;
}

static void start_refresh_test() {
  fl_rect left_rect;
  left_rect.x      = 200;
  left_rect.y      = 100;
  left_rect.width  = 600;
  left_rect.height = 100;
  auto left_test   = new refresh_test_service(left_rect, 6);
  left_test->start();
}

void pack_test_bar::create_children() {
  add_but_item("Refresh", [=]() { start_refresh_test(); });
}

void pack_test_bar::after_create_widget() {
  fl_lvgl_delay([=](void* arg) { start_refresh_test(); }, 3000);
}

lv_obj_t* pack_test_bar::add_but_item(string text, test_cb_t cb) {
  auto but = create_fl_button(view, text.c_str(), true, 120, 60);
  fl_obj_add_event_cb(
    but,
    [=](void* arg) {
      if (cb) {
        cb();
      }
    },
    LV_EVENT_CLICKED);
  return but;
}

void refresh_test_service::start() {
  this->frame = create_fl_lv_obj(lv_layer_top());
  lv_obj_set_style_bg_opa(frame, 0, LV_PART_MAIN);
  lv_obj_set_size(frame, area.width, area.height);
  lv_obj_set_pos(frame, area.x, area.y);

  this->current_index = count;
  fl_lvgl_delay([=](void* arg) { start_inner(); }, 500);

  this->cont = create_fl_lv_obj(frame);
  lv_obj_set_size(cont, lv_pct(100), lv_pct(100));
  lv_obj_set_style_bg_color(cont, color_make(0xff), LV_PART_MAIN);
}

void refresh_test_service::start_inner() {
  ESP_LOGW("========", "start");
  auto time_space = 1000;

  lv_obj_set_style_bg_color(cont, color_make(0xff), LV_PART_MAIN); 

  // 切换渲染位置
  if (this->current_index == count - 2) {
      ESP_LOGW("========", "change");
    lv_obj_set_pos(this->frame, area.x, area.y + area.height + 300);
  }

  // this->cont = create_fl_lv_obj(frame);
  // lv_obj_set_size(cont, lv_pct(100), lv_pct(100));
  // lv_obj_set_style_bg_color(cont, color_make(0xff), LV_PART_MAIN);

  // lv_obj_set_style_pad_all(cont, 20, LV_PART_MAIN);
  // auto cont_label = create_fl_label(cont);
  // lv_obj_set_width(cont_label, lv_pct(100));
  // lv_label_set_text(cont_label,
  //                   "IT NEED WELL ADAPTED TO BUSINESS LOGIC, THE THREAD'S "
  //                   "RESUME, SUSPEND MUST CALLED IN UI THREAD, BECAUSE THERE "
  //                   "WILL BE THREAD SYNCHRONIZATION ISSUES.");
  // lv_label_set_long_mode(cont_label, LV_LABEL_LONG_WRAP);


  fl_lvgl_delay(
    [=](void* arg) {
      ESP_LOGW("========", "delete");
      if (cont) {
        lv_obj_set_style_bg_color(cont, color_make(0x00), LV_PART_MAIN); 
        // lv_obj_del(cont);
      }
      this->current_index--;

      if (current_index > 0) {
        fl_lvgl_delay([=](void* arg) { start_inner(); }, time_space);
      } else {
        auto on_cl = this->on_close;
        this->clear();
        if (on_cl) {
          on_cl();
        }
      }
    },
    time_space);
};

void refresh_test_service::clear() {
  lv_obj_del(frame);
  delete this;
}

void pack_test_bar::add_test_bar() {
  create_fl_widget(new pack_test_bar(), lv_layer_top());
}