#include "esp_sleep.h"

esp_err_t esp_sleep_disable_wakeup_source(esp_sleep_source_t source) {
  return ESP_OK;
}

esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us) {
  return ESP_OK;
}

esp_err_t esp_sleep_enable_ext0_wakeup(gpio_num_t gpio_num, int level) {
  return ESP_OK;
}

esp_err_t esp_sleep_enable_gpio_wakeup(void) {
  return ESP_OK;
}

esp_err_t esp_light_sleep_start(void) {
  return ESP_OK;
}

esp_err_t esp_deep_sleep_start(void) {
  return ESP_OK;
}

esp_err_t esp_sleep_pd_config(esp_sleep_pd_domain_t domain,
                              esp_sleep_pd_option_t option) {
  return ESP_OK;
}
