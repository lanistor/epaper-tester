#include "fl_widget.h"
#include "./ui_utils.h"
#include "fl_utils.h"
#include <iostream>

static void view_delete_cb(lv_event_t* e) {
  lv_obj_t* target = lv_event_get_target(e);
  auto      widget = (fl_widget*)(target->user_data);
  if (widget->view == target) {
    delete widget;
  }
}

fl_widget::fl_widget(bool clean_on_update) {
  this->clean_on_update = clean_on_update;
};

fl_widget::fl_widget(string name, bool clean_on_update) {
  this->name            = name;
  this->clean_on_update = clean_on_update;
};

fl_widget::~fl_widget() {
  this->par  = NULL;
  this->view = NULL;
}

void fl_widget::update_widget() {
  if (clean_on_update) {
    lv_obj_clean(this->view);
  }

  this->before_update_widget();
  this->create_children();
  this->after_update_widget();
}

fl_widget*
create_fl_widget(fl_widget* widget, lv_obj_t* par, reset_widget_cb reset_cb) {
  widget->par = par;

  widget->before_create_widget();

  lv_obj_t* view = widget->create_widget();

  if (reset_cb) {
    reset_cb(view);
  }

  widget->view    = view;
  view->user_data = widget;

  widget->create_children();

  lv_obj_add_event_cb(view, view_delete_cb, LV_EVENT_DELETE, NULL);

  widget->after_create_widget();

  return widget;
}
