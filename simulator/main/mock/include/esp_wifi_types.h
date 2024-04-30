#pragma once

enum wifi_auth_mode_t {
  WIFI_AUTH_OPEN = 0, /**< authenticate mode : open */
  WIFI_AUTH_WEP, /**< authenticate mode : WEP */
  WIFI_AUTH_WPA_PSK, /**< authenticate mode : WPA_PSK */
  WIFI_AUTH_WPA2_PSK, /**< authenticate mode : WPA2_PSK */
  WIFI_AUTH_WPA_WPA2_PSK, /**< authenticate mode : WPA_WPA2_PSK */
  WIFI_AUTH_WPA2_ENTERPRISE, /**< authenticate mode : WPA2_ENTERPRISE */
  WIFI_AUTH_WPA3_PSK, /**< authenticate mode : WPA3_PSK */
  WIFI_AUTH_WPA2_WPA3_PSK, /**< authenticate mode : WPA2_WPA3_PSK */
  WIFI_AUTH_WAPI_PSK, /**< authenticate mode : WAPI_PSK */
  WIFI_AUTH_MAX
};
