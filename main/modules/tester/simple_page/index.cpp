#include "./index.h"

const char* text_1 =
  "We trained this model using Reinforcement Learning from Human Feedback "
  "(RLHF), using the same methods as InstructGPT, but with slight differences "
  "in the data collection setup. We trained an initial model using supervised "
  "fine-tuning: human AI trainers provided conversations in which they played "
  "both sides—the user and an AI assistant. We gave the trainers access to "
  "We trained this model using Reinforcement Learning from Human Feedback "
  "(RLHF), using the same methods as InstructGPT, but with slight differences "
  "in the data collection setup. We trained an initial model using supervised "
  "fine-tuning: human AI trainers provided conversations in which they played "
  "both sides—the user and an AI assistant. We gave the trainers access to "
  "fine-tuning: human AI trainers provided conversations in which they played "
  "both sides—the user and an AI assistant. We gave the trainers access to ";

lv_obj_t* tester_simple_page::create_widget() {
  auto view = create_fl_flex_obj(par, LV_FLEX_FLOW_ROW);
  lv_obj_set_size(view, lv_pct(100), lv_pct(100));
  return view;
}

void tester_simple_page::create_children() {
  // column 1
  auto col_1 = create_fl_flex_obj(view, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_height(col_1, lv_pct(100));
  lv_obj_set_flex_grow(col_1, 2);
  lv_obj_set_style_pad_all(col_1, 15, LV_PART_MAIN);

  // column 1 row 1
  auto col_1_row_1 = create_fl_flex_obj(col_1, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_width(col_1_row_1, lv_pct(100));
  lv_obj_set_flex_grow(col_1_row_1, 1);
  auto col_1_row_1_label = create_fl_label(col_1_row_1);
  lv_label_set_text(col_1_row_1_label, text_1);
  lv_obj_set_width(col_1_row_1_label, lv_pct(100));
  lv_label_set_long_mode(col_1_row_1_label, LV_LABEL_LONG_WRAP);

  // column 1 row 2
  auto col_1_row_2 = create_fl_flex_obj(col_1, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_width(col_1_row_2, lv_pct(100));
  lv_obj_set_flex_grow(col_1_row_2, 1);
  auto col_1_row_2_label = create_fl_label(col_1_row_2);
  lv_label_set_text(col_1_row_2_label, text_1);
  lv_obj_set_width(col_1_row_2_label, lv_pct(100));
  lv_label_set_long_mode(col_1_row_2_label, LV_LABEL_LONG_WRAP);

  // column 2
  // auto col_2 = create_fl_flex_obj(view, LV_FLEX_FLOW_COLUMN);
  // lv_obj_set_height(col_2, lv_pct(100));
  // lv_obj_set_flex_grow(col_2, 1);
}
