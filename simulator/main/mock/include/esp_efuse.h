#pragma once

/**
 * @brief Type of eFuse blocks for ESP32
 */
typedef enum {
  EFUSE_BLK0 = 0, /**< Number of eFuse block. Reserved. */

  EFUSE_BLK1 =
    1, /**< Number of eFuse block. Used for Flash Encryption. If not using that Flash Encryption feature, they can be used for another purpose. */
  EFUSE_BLK_KEY0 =
    1, /**< Number of eFuse block. Used for Flash Encryption. If not using that Flash Encryption feature, they can be used for another purpose. */
  EFUSE_BLK_ENCRYPT_FLASH =
    1, /**< Number of eFuse block. Used for Flash Encryption. If not using that Flash Encryption feature, they can be used for another purpose. */

  EFUSE_BLK2 =
    2, /**< Number of eFuse block. Used for Secure Boot. If not using that Secure Boot feature, they can be used for another purpose. */
  EFUSE_BLK_KEY1 =
    2, /**< Number of eFuse block. Used for Secure Boot. If not using that Secure Boot feature, they can be used for another purpose. */
  EFUSE_BLK_SECURE_BOOT =
    2, /**< Number of eFuse block. Used for Secure Boot. If not using that Secure Boot feature, they can be used for another purpose. */

  EFUSE_BLK3 =
    3, /**< Number of eFuse block. Uses for the purpose of the user. */
  EFUSE_BLK_KEY2 =
    3, /**< Number of eFuse block. Uses for the purpose of the user. */
  EFUSE_BLK_KEY_MAX = 4,

  EFUSE_BLK_MAX = 4,
} esp_efuse_block_t;

/**
 * @brief Type definition for an eFuse field
 */
typedef struct {
  esp_efuse_block_t efuse_block : 8; /**< Block of eFuse */
  uint8_t           bit_start; /**< Start bit [0..255] */
  uint16_t          bit_count; /**< Length of bit field [1..-]*/
} esp_efuse_desc_t;
