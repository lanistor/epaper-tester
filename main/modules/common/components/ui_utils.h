#pragma once

#include "basic.h"
#include <functional>
#include <string>
#include <vector>

using namespace std;

class lv_event_record_t
{
public:
  lv_obj_t *target = NULL;
  int64_t timestamp = 0;
};

// 代替 lv_event_cb_t , 支持lamda表达式
typedef function<void(void *user_data)> fl_event_cb;

lv_color_t color_make(uint8_t value);

void add_default_style_of_cont(lv_obj_t *view);

lv_obj_t *create_fl_lv_obj(lv_obj_t *par);

lv_obj_t *create_fl_flex_obj(lv_obj_t *par, lv_flex_flow_t flow);

lv_obj_t *create_fl_label(lv_obj_t *par, bool add_default_font = true);

lv_obj_t *create_fl_button(lv_obj_t *par,
                           string label,
                           bool plain = false,
                           int width = 200,
                           int height = 55,
                           int radius = 6);

struct common_lv_event_cb_model
{
  fl_event_cb func = NULL;
  void *user_data = NULL;
  int64_t throttle = 1000;
};
struct _lv_event_dsc_t *fl_obj_add_event_cb(lv_obj_t *obj,
                                            fl_event_cb event_cb,
                                            lv_event_code_t filter,
                                            void *user_data = NULL,
                                            int64_t throttle = 1000);
