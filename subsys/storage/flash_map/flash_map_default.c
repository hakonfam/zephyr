/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <flash_map.h>

const struct flash_area default_flash_map[] = {
	{
		.fa_id = 0,
		.fa_off = DT_FLASH_AREA_MCUBOOT_OFFSET,
		.fa_dev_name = DT_FLASH_AREA_0_DEV,
		.fa_size = DT_FLASH_AREA_MCUBOOT_SIZE,
	},{
		.fa_id = 1,
		.fa_off = DT_FLASH_AREA_IMAGE_0_OFFSET,
		.fa_dev_name = DT_FLASH_AREA_0_DEV,
		.fa_size = DT_FLASH_AREA_IMAGE_0_SIZE,
	},{
		.fa_id = 2,
		.fa_off = DT_FLASH_AREA_IMAGE_1_OFFSET,
		.fa_dev_name = DT_FLASH_AREA_0_DEV,
		.fa_size = DT_FLASH_AREA_IMAGE_1_SIZE,
	},{
		.fa_id = 3,
		.fa_off = DT_FLASH_AREA_IMAGE_SCRATCH_OFFSET,
		.fa_dev_name = DT_FLASH_AREA_0_DEV,
		.fa_size = DT_FLASH_AREA_IMAGE_SCRATCH_SIZE,
	},{
		.fa_id = 4,
		.fa_off = DT_FLASH_AREA_STORAGE_OFFSET,
		.fa_dev_name = DT_FLASH_AREA_0_DEV,
		.fa_size = DT_FLASH_AREA_STORAGE_SIZE,
	},
};

const int flash_map_entries = ARRAY_SIZE(default_flash_map);
const struct flash_area *flash_map = default_flash_map;
