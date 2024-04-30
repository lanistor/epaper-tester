#include "./epdiy_epaper.h"

/* Configure your display */
void epdiy_init(void) {}

/* LVGL callbacks */
void epdiy_flush(lv_disp_drv_t*   drv,
                 const lv_area_t* area,
                 lv_color_t*      color_map) {}

/* Sets a pixel in *buf temporary buffer that comes afterwards in flush as *image_map */
void epdiy_set_px_cb(lv_disp_drv_t* disp_drv,
                     uint8_t*       buf,
                     lv_coord_t     buf_w,
                     lv_coord_t     x,
                     lv_coord_t     y,
                     lv_color_t     color,
                     lv_opa_t       opa) {}

/* refresh all screen */
void epdiy_repaint_all() {}

/* refresh area */
void epdiy_repaint(EpdRect area) {}

void set_epdiy_flush_type_cb(epdiy_flush_type_cb_t cb) {}
