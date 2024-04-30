#include "epd_driver.h"
#include "esp_freertos_hooks.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "../../tester/pack/index.h"
#include "../widget.h"
#include "./index.h"
#include "components.h"
#include "fl_utils.h"

#ifdef CONFIG_LV_TOUCH_CONTROLLER_L58
  #include "L58Touch.h"
#endif

#define _APP_TAG "APP"

lv_style_t lv_cont_default_style;
lv_style_t fl_style_font;

static void clock_refreshed_runner();
static bool _clock_inited = false;
static bool _app_initing  = false;

void fl_before_start(void) {
  theme_init();
}

void start_application(void) {
  create_fl_widget(new root_widget(), lv_scr_act());
}

void fl_after_start() {
  pack_test_bar::add_test_bar();
}

void theme_init() {
  lv_theme_default_init(lv_disp_get_default(), color_make(0x00),
                        color_make(0x80), false, &lv_font_montserrat_24);

  lv_style_init(&fl_style_font);
  lv_style_set_text_font(&fl_style_font, &lv_font_montserrat_24);

  lv_style_init(&lv_cont_default_style);
  lv_style_set_border_width(&lv_cont_default_style, 0);
  lv_style_set_pad_all(&lv_cont_default_style, 0);
  lv_style_set_radius(&lv_cont_default_style, 0);
}
