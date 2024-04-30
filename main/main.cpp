#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_LV_LOG 1
#include "lv_conf.h"

#include "basic.h"
#include "fl_utils.h"
#include "modules/app/index.h"
#include <time.h>
#

#define _GUI_TAG "GUI_TASK"

extern "C"
{
  void app_main();
}

static void hardware_init();
static void gui_task(void *);

static void lv_tick_task(void *);

lv_disp_drv_t disp_drv;

esp_timer_handle_t lvgl_tick_periodic_timer;

void app_main()
{
  gpio_install_isr_service(0);

  hardware_init();

  lvgl_driver_init();

  lv_init();

  xTaskCreatePinnedToCore(gui_task, "gui_task", 1024 * 16, NULL, 5, NULL, 0);
}

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t gui_semaphore;

static void gui_task(void *arg)
{
  (void)arg;
  ESP_LOGI(_GUI_TAG, "gui_task started");
  gui_semaphore = xSemaphoreCreateMutex();

  int display_width = epd_rotated_display_width();
  int display_height = epd_rotated_display_height();

  ESP_LOGI(_GUI_TAG, "epd_display_width: %d ; epd_display_height: %d ",
           display_width, display_height);

  int display_pixel_size = display_width * display_height; // 160;

  lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(
      display_pixel_size * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
  assert(buf1 != NULL);

  static lv_color_t *buf2 = NULL;

  static lv_disp_draw_buf_t disp_buf;

  /* Initialize the working buffer depending on the selected display.
   * NOTE: buf2 == NULL when using monochrome displays. */
  lv_disp_draw_buf_init(&disp_buf, buf1, buf2, display_pixel_size);

  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = display_width;
  disp_drv.ver_res = display_height;
  disp_drv.flush_cb = disp_driver_flush;

  ESP_LOGI(_GUI_TAG, "address of disp_drv: %p", &disp_drv);

  disp_drv.draw_buf = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touch_driver_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.long_press_time = 800; // 长按响应时长修改
  lv_indev_drv_register(&indev_drv);
#endif

  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task,
      .name = "lvgl_tick_periodic_timer",
  };

  ESP_ERROR_CHECK(
      esp_timer_create(&periodic_timer_args, &lvgl_tick_periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_periodic_timer,
                                           LV_TICK_PERIOD_MS * 1000));

  fl_before_start();
  start_application();
  fl_after_start();

  /* Force screen refresh */
  lv_refr_now(NULL);

  while (1)
  {
    run_safe_async_list();

    // Try to take the semaphore, call lvgl related function on success
    if (pdTRUE == xSemaphoreTake(gui_semaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(gui_semaphore);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }

  /* A task should NEVER return */
  free(buf1);
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
  free(buf2);
#endif
  vTaskDelete(NULL);
}

static void hardware_init()
{
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  ESP_LOGI(TAG, "hardware inited: nvs, power, buzzer");
}

static void lv_tick_task(void *arg)
{
  (void)arg;
  lv_tick_inc(LV_TICK_PERIOD_MS);
}