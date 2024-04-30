#include "esp_timer.h"
#include "basic.h"
#include "esp_err.h"
#include "esp_log.h"

void _timer_period_cb(_lv_timer_t* arg) {
  auto handler = (esp_timer_handle_t)arg->user_data;
  handler->callback(handler->arg);
}

void _timer_once_cb(_lv_timer_t* arg) {
  auto handler = (esp_timer_handle_t)arg->user_data;
  handler->callback(handler->arg);

  esp_timer_delete(handler);
}

esp_err_t esp_timer_create(const esp_timer_create_args_t* create_args,
                           esp_timer_handle_t*            handler) {
  auto result      = (esp_timer_t*)malloc(sizeof(esp_timer_t));
  result->callback = create_args->callback;
  result->arg      = create_args->arg;
  result->name     = create_args->name;
  result->timer    = NULL;

  *handler = result;
  return ESP_OK;
}

esp_err_t esp_timer_start_periodic(esp_timer_handle_t handler,
                                   uint64_t           timeout_us) {
  if (handler->timer == NULL) {
    auto _lv_timer =
      lv_timer_create(_timer_period_cb, (uint32_t)(timeout_us / 1000), handler);
    handler->timer = _lv_timer;
  } else {
    lv_timer_resume(handler->timer);
  }
  return ESP_OK;
}

esp_err_t esp_timer_start_once(esp_timer_handle_t handler,
                               uint64_t           timeout_us) {
  auto _lv_timer =
    lv_timer_create(_timer_once_cb, (uint32_t)(timeout_us / 1000), handler);
  handler->timer = _lv_timer;
  return ESP_OK;
}

esp_err_t esp_timer_stop(esp_timer_handle_t handler) {
  if (handler && handler->timer) {
    lv_timer_pause(handler->timer);
  }
  return ESP_OK;
}

esp_err_t esp_timer_delete(esp_timer_handle_t handler) {
  if (handler) {
    if (handler->timer != NULL) {
      lv_timer_del(handler->timer);
    }
    free(handler);
  }
  return ESP_OK;
}
