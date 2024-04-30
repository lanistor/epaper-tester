#include "fl_async.h"
#include "esp_log.h"
#include "fl_utils.h"
#include <vector>

vector<fl_async_arg_model *> safe_async_list;

static void _async_cb(void *arg)
{
  auto arg_model = (fl_async_arg_model *)arg;

  auto cb = arg_model->cb;
  auto real_arg = arg_model->arg;

  delete arg_model;
  cb(real_arg);
}

static void _timer_cb(_lv_timer_t *arg)
{
  auto arg_model = (fl_timer_arg_model *)arg->user_data;

  auto cb = arg_model->cb;
  auto real_arg = arg_model->arg;
  auto once = arg_model->once;

  if (once)
  {
    delete arg_model;
  }

  cb(real_arg);

  if (once)
  {
    lv_timer_del(arg);
  }
}

void fl_lvgl_async(fl_async_cb cb, void *data, string name)
{
  auto arg = new fl_async_arg_model(cb, data, name);
  lv_async_call(_async_cb, arg);
}

void fl_lvgl_safe_async(fl_async_cb cb, void *data, string name)
{
  auto arg = new fl_async_arg_model(cb, data, name);
  safe_async_list.push_back(arg);
}

void run_safe_async_list()
{
  while (safe_async_list.size())
  {
    auto target_ptr = safe_async_list.begin();
    auto target = *target_ptr;
    safe_async_list.erase(target_ptr);
    _async_cb(target);
  }
}

lv_timer_t *fl_lvgl_delay(fl_async_cb cb, int ms, void *data, string name)
{
  auto arg = new fl_timer_arg_model(cb, data, true, false, name);
  assert(ms <= 60 * 1000); // fl_delay 延时不能超过60s
  return lv_timer_create(_timer_cb, ms, arg);
}

void fl_lvgl_timer_del(lv_timer_t *timer_value)
{
  lv_timer_del(timer_value);
}
