/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "sdkconfig.h"
#include "esp_efuse.h"
#include <assert.h>
#include "esp_efuse_custom_table.h"

// md5_digest_table 23459d50d729b9384df118c084fd41f2
// This file was generated from the file esp_efuse_custom_table.csv. DO NOT CHANGE THIS FILE MANUALLY.
// If you want to change some fields, you need to change esp_efuse_custom_table.csv file
// then run `efuse_common_table` or `efuse_custom_table` command it will generate this file.
// To show efuse_table run the command 'show_efuse_table'.

#define MAX_BLK_LEN CONFIG_EFUSE_MAX_BLK_LEN

// The last free bit in the block is counted over the entire file.
#define LAST_FREE_BIT_BLK3 248

_Static_assert(LAST_FREE_BIT_BLK3 <= MAX_BLK_LEN, "The eFuse table does not match the coding scheme. Edit the table and restart the efuse_common_table or efuse_custom_table command to regenerate the new files.");

static const esp_efuse_desc_t SERIAL_NUMBER[] = {
    {EFUSE_BLK3, 160, 24}, 	 // Serial Number,
    {EFUSE_BLK3, 192, 56}, 	 // Serial Number,
};





const esp_efuse_desc_t* ESP_EFUSE_SERIAL_NUMBER[] = {
    &SERIAL_NUMBER[0],    		// Serial Number
    &SERIAL_NUMBER[1],    		// Serial Number
    NULL
};
