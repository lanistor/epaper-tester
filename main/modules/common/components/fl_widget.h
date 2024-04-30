#pragma once

#include <functional>
#include <map>
#include <set>
#include <string>

#include "basic.h"

using namespace std;

class fl_widget
{
public:
  string name;
  lv_obj_t *par = NULL;
  lv_obj_t *view = NULL;

protected:
  bool clean_on_update = true;

public:
  fl_widget(bool clean_on_update = true);
  fl_widget(string name, bool clean_on_update = true);
  virtual ~fl_widget();

public:
  virtual string get_name()
  {
    return this->name;
  }

public:
  virtual void before_create_widget() {};
  virtual lv_obj_t *create_widget() = 0;

  virtual void create_children() {};

  virtual void after_create_widget() {};

  virtual void before_update_widget() {}

  virtual void update_widget();

  virtual void after_update_widget() {};
};

typedef function<void(lv_obj_t *view)> reset_widget_cb;

extern fl_widget *create_fl_widget(fl_widget *widget,
                                   lv_obj_t *par,
                                   reset_widget_cb reset_cb = NULL);

template <typename T>
T *get_user_data_of_lv_obj(lv_obj_t *view)
{
  return (T *)view->user_data;
}
