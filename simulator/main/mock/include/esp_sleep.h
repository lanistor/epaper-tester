#pragma once

#include "esp_basic.h"
#include "esp_err.h"
#include "gpio_types.h"

/**
 * @brief Logic function used for EXT1 wakeup mode.
 */
#if CONFIG_IDF_TARGET_ESP32
typedef enum {
  ESP_EXT1_WAKEUP_ALL_LOW =
    0,  //!< Wake the chip when all selected GPIOs go low
  ESP_EXT1_WAKEUP_ANY_HIGH =
    1  //!< Wake the chip when any of the selected GPIOs go high
} esp_sleep_ext1_wakeup_mode_t;
#else
typedef enum {
  ESP_EXT1_WAKEUP_ANY_LOW =
    0,  //!< Wake the chip when any of the selected GPIOs go low
  ESP_EXT1_WAKEUP_ANY_HIGH =
    1,  //!< Wake the chip when any of the selected GPIOs go high
  ESP_EXT1_WAKEUP_ALL_LOW __attribute__((
    deprecated("wakeup mode \"ALL_LOW\" is no longer supported after ESP32, \
    please use ESP_EXT1_WAKEUP_ANY_LOW instead"))) = ESP_EXT1_WAKEUP_ANY_LOW
} esp_sleep_ext1_wakeup_mode_t;
#endif

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP
typedef enum {
  ESP_GPIO_WAKEUP_GPIO_LOW  = 0,
  ESP_GPIO_WAKEUP_GPIO_HIGH = 1
} esp_deepsleep_gpio_wake_up_mode_t;
#endif

/**
 * @brief Power domains which can be powered down in sleep mode
 */
typedef enum {
  ESP_PD_DOMAIN_RTC_PERIPH,  //!< RTC IO, sensors and ULP co-processor
  ESP_PD_DOMAIN_RTC_SLOW_MEM,  //!< RTC slow memory
  ESP_PD_DOMAIN_RTC_FAST_MEM,  //!< RTC fast memory
  ESP_PD_DOMAIN_XTAL,  //!< XTAL oscillator
#if SOC_PM_SUPPORT_CPU_PD
  ESP_PD_DOMAIN_CPU,  //!< CPU core
#endif
  ESP_PD_DOMAIN_RTC8M,  //!< Internal 8M oscillator
  ESP_PD_DOMAIN_VDDSDIO,  //!< VDD_SDIO
  ESP_PD_DOMAIN_MAX  //!< Number of domains
} esp_sleep_pd_domain_t;

/**
 * @brief Power down options
 */
typedef enum {
  ESP_PD_OPTION_OFF,  //!< Power down the power domain in sleep mode
  ESP_PD_OPTION_ON,  //!< Keep power domain enabled during sleep mode
  ESP_PD_OPTION_AUTO  //!< Keep power domain enabled in sleep mode, if it is needed by one of the wakeup options. Otherwise power it down.
} esp_sleep_pd_option_t;

/**
 * @brief Sleep wakeup cause
 */
typedef enum {
  ESP_SLEEP_WAKEUP_UNDEFINED,  //!< In case of deep sleep, reset was not caused by exit from deep sleep
  ESP_SLEEP_WAKEUP_ALL,  //!< Not a wakeup cause, used to disable all wakeup sources with esp_sleep_disable_wakeup_source
  ESP_SLEEP_WAKEUP_EXT0,  //!< Wakeup caused by external signal using RTC_IO
  ESP_SLEEP_WAKEUP_EXT1,  //!< Wakeup caused by external signal using RTC_CNTL
  ESP_SLEEP_WAKEUP_TIMER,  //!< Wakeup caused by timer
  ESP_SLEEP_WAKEUP_TOUCHPAD,  //!< Wakeup caused by touchpad
  ESP_SLEEP_WAKEUP_ULP,  //!< Wakeup caused by ULP program
  ESP_SLEEP_WAKEUP_GPIO,  //!< Wakeup caused by GPIO (light sleep only on ESP32, S2 and S3)
  ESP_SLEEP_WAKEUP_UART,  //!< Wakeup caused by UART (light sleep only)
  ESP_SLEEP_WAKEUP_WIFI,  //!< Wakeup caused by WIFI (light sleep only)
  ESP_SLEEP_WAKEUP_COCPU,  //!< Wakeup caused by COCPU int
  ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG,  //!< Wakeup caused by COCPU crash
  ESP_SLEEP_WAKEUP_BT,  //!< Wakeup caused by BT (light sleep only)
} esp_sleep_source_t;

esp_err_t esp_sleep_disable_wakeup_source(esp_sleep_source_t source);

esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us);

esp_err_t esp_sleep_enable_ext0_wakeup(gpio_num_t gpio_num, int level);

esp_err_t esp_sleep_enable_gpio_wakeup(void);

esp_err_t esp_light_sleep_start(void);

esp_err_t esp_deep_sleep_start(void);

esp_err_t esp_sleep_pd_config(esp_sleep_pd_domain_t domain,
                              esp_sleep_pd_option_t option);
