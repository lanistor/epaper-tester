#include "ui_utils.h"
#include "epd_driver.h"
#include "fl_icon.h"
#include "fl_utils.h"

// 通用 lv event 回调
static void common_lv_event_cb(lv_event_t *e);

void add_default_style_of_cont(lv_obj_t *view)
{
  lv_obj_add_style(view, &lv_cont_default_style, LV_PART_MAIN);
}

lv_color_t color_make(uint8_t value)
{
#if RENDER_MONOCHROME == 1
  if (value <= 0xcc)
  {
    value = 0x00;
  }
  else
  {
    value = 0xff;
  }
#endif

#if LV_COLOR_DEPTH == 32
  lv_color_t c;
  c.ch.red = value;
  c.ch.green = value;
  c.ch.blue = value;
  c.ch.alpha = 255;
  c.full = lv_color_to32(c);
  return c;
#else
  // for COLOR_DEPTH: 1 / 8
  lv_color_t c;
  c.full = value;
  return c;
#endif
}

lv_obj_t *create_fl_lv_obj(lv_obj_t *par)
{
  lv_obj_t *view = lv_obj_create(par);
  add_default_style_of_cont(view);

  lv_obj_clear_flag(view, LV_OBJ_FLAG_SCROLL_MOMENTUM);
  lv_obj_clear_flag(view, LV_OBJ_FLAG_SCROLL_ELASTIC);
  return view;
}

lv_obj_t *create_fl_flex_obj(lv_obj_t *par, lv_flex_flow_t flow)
{
  lv_obj_t *view = create_fl_lv_obj(par);
  lv_obj_set_layout(view, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(view, flow);
  if (flow == LV_FLEX_FLOW_ROW || flow == LV_FLEX_FLOW_ROW_REVERSE ||
      flow == LV_FLEX_FLOW_ROW_WRAP || flow == LV_FLEX_FLOW_ROW_WRAP_REVERSE)
  {
    lv_obj_set_style_pad_column(view, 0, LV_PART_MAIN);
  }
  else if (flow == LV_FLEX_FLOW_COLUMN ||
           flow == LV_FLEX_FLOW_COLUMN_REVERSE)
  {
    lv_obj_set_style_pad_row(view, 0, LV_PART_MAIN);
  }
  return view;
}

lv_obj_t *create_fl_label(lv_obj_t *par, bool add_default_font)
{
  lv_obj_t *label = lv_label_create(par);
  add_default_style_of_cont(label);
  if (add_default_font)
  {
    lv_obj_add_style(label, &fl_style_font, LV_PART_MAIN);
  }
  return label;
}

// 创建默认 button
lv_obj_t *create_fl_button(lv_obj_t *par,
                           string label,
                           bool plain,
                           int width,
                           int height,
                           int radius)
{
  auto but = lv_btn_create(par);

  lv_obj_set_style_radius(but, radius, LV_PART_MAIN);
  lv_obj_set_style_shadow_opa(but, 0, LV_PART_MAIN);
  if (width > 0)
  {
    lv_obj_set_width(but, width);
  }
  if (height > 0)
  {
    lv_obj_set_height(but, height);
  }

  auto but_text = create_fl_label(but, false);
  lv_obj_set_style_text_font(but_text, &lv_font_montserrat_24, LV_PART_MAIN);
  lv_label_set_text(but_text, label.c_str());
  lv_obj_center(but_text);

  lv_obj_set_style_border_side(but, LV_BORDER_SIDE_NONE, LV_PART_MAIN);
  lv_obj_set_style_bg_color(but, plain ? color_make(0xff) : color_make(0x00),
                            LV_PART_MAIN);
  lv_obj_set_style_text_color(but, plain ? color_make(0x00) : color_make(0xff),
                              LV_PART_MAIN);

  return but;
}

static void fl_add_event_view_delete_cb(lv_event_t *e)
{
  auto user_data = (common_lv_event_cb_model *)lv_event_get_user_data(e);
  if (user_data)
  {
    e->user_data = NULL;
    delete user_data;
  }
}

static lv_event_record_t last_click;

static void common_lv_event_cb(lv_event_t *e)
{
  auto param = (common_lv_event_cb_model *)e->user_data;
  auto func = param->func;
  auto user_data = param->user_data;
  func(user_data);
}

struct _lv_event_dsc_t *fl_obj_add_event_cb(lv_obj_t *obj,
                                            fl_event_cb event_cb,
                                            lv_event_code_t filter,
                                            void *user_data,
                                            int64_t throttle)
{
  auto mod = new common_lv_event_cb_model();
  mod->func = event_cb;
  mod->user_data = user_data;
  mod->throttle = throttle;

  lv_obj_add_event_cb(obj, fl_add_event_view_delete_cb, LV_EVENT_DELETE, mod);

  return lv_obj_add_event_cb(obj, common_lv_event_cb, filter, mod);
}
