#pragma once

/** Enable display power supply. */
void epd_poweron();

/** Disable display power supply. */
void epd_poweroff();

/** Get screen width after rotation */
int epd_rotated_display_width();

/** Get screen height after rotation */
int epd_rotated_display_height();