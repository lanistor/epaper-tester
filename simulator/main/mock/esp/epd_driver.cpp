#include "epd_driver.h"
#include "lv_drv_conf.h"

void epd_poweron() {}

/** Disable display power supply. */
void epd_poweroff() {}

/** Get screen width after rotation */
int epd_rotated_display_width() {
  return MONITOR_HOR_RES;
}

/** Get screen height after rotation */
int epd_rotated_display_height() {
  return MONITOR_VER_RES;
}