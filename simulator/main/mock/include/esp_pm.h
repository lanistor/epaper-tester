#pragma once

#include "esp_err.h"

typedef struct esp_pm_lock {
} esp_pm_lock_t;

typedef enum {
  ESP_PM_CPU_FREQ_MAX,
  ESP_PM_APB_FREQ_MAX,
  ESP_PM_NO_LIGHT_SLEEP,
} esp_pm_lock_type_t;

typedef struct esp_pm_lock* esp_pm_lock_handle_t;

esp_err_t esp_pm_lock_acquire(esp_pm_lock_handle_t handle) {
  return ESP_OK;
}

esp_err_t esp_pm_lock_release(esp_pm_lock_handle_t handle) {
  return ESP_OK;
}

esp_err_t esp_pm_lock_create(esp_pm_lock_type_t    lock_type,
                             int                   arg,
                             const char*           name,
                             esp_pm_lock_handle_t* out_handle) {
  return ESP_OK;
}
