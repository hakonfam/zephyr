/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <flash_map.h>

#if defined(DT_FLASH_DEV_NAME)
#define FA_DEV_ID SOC_FLASH_0_ID
#elif defined(CONFIG_SPI_FLASH_W25QXXDV) || defined(DT_SPI_NOR_DRV_NAME)
#define FA_DEV_ID SPI_FLASH_0_ID
#endif

#include <pm_config.h>
#define SLOT_SIZE (PM_CFG_APP_SIZE / 2)
#define FLASH_AREA_IMAGE_0_OFFSET (PM_CFG_APP_ADDRESS)
#define FLASH_AREA_IMAGE_0_SIZE SLOT_SIZE
#define FLASH_AREA_IMAGE_1_OFFSET FLASH_AREA_IMAGE_0_OFFSET + FLASH_AREA_IMAGE_0_SIZE
#define FLASH_AREA_IMAGE_1_SIZE FLASH_AREA_IMAGE_0_SIZE
#define FLASH_AREA_IMAGE_SCRATCH_OFFSET PM_CFG_MCUBOOT_SCRATCH_ADDRESS
#define FLASH_AREA_IMAGE_SCRATCH_SIZE PM_CFG_MCUBOOT_SCRATCH_SIZE
#define FLASH_AREA_IMAGE_STORAGE_OFFSET PM_CFG_MCUBOOT_STORAGE_ADDRESS
#define FLASH_AREA_IMAGE_STORAGE_SIZE PM_CFG_MCUBOOT_STORAGE_SIZE
#define FLASH_AREA_MCUBOOT_OFFSET PM_CFG_MCUBOOT_ADDRESS
#define FLASH_AREA_MCUBOOT_SIZE PM_CFG_MCUBOOT_SIZE

const struct flash_area default_flash_map[] = {
	/* FLASH_AREA_BOOTLOADER */
	{
		.fa_id = 0,
		.fa_device_id = FA_DEV_ID,
		.fa_off = FLASH_AREA_MCUBOOT_OFFSET,
		.fa_size = FLASH_AREA_MCUBOOT_SIZE,
	},

	/* FLASH_AREA_IMAGE_0 */
	{
		.fa_id = 1,
		.fa_device_id = FA_DEV_ID,
		.fa_off = FLASH_AREA_IMAGE_0_OFFSET,
		.fa_size = FLASH_AREA_IMAGE_0_SIZE,
	},

	/* FLASH_AREA_IMAGE_1 */
	{
		.fa_id = 2,
		.fa_device_id = FA_DEV_ID,
		.fa_off = FLASH_AREA_IMAGE_1_OFFSET,
		.fa_size = FLASH_AREA_IMAGE_1_SIZE,
	},

	/* FLASH_AREA_IMAGE_SCRATCH */
	{
		.fa_id = 3,
		.fa_device_id = FA_DEV_ID,
		.fa_off = FLASH_AREA_IMAGE_SCRATCH_OFFSET,
		.fa_size = FLASH_AREA_IMAGE_SCRATCH_SIZE,
	},

#ifdef CONFIG_FS_FLASH_STORAGE_PARTITION
	/* FLASH_AREA_STORAGE */
	{
		.fa_id = 4,
		.fa_device_id = FA_DEV_ID,
		.fa_off = FLASH_AREA_STORAGE_OFFSET,
		.fa_size = FLASH_AREA_STORAGE_SIZE,
	},
#endif
};

const int flash_map_entries = ARRAY_SIZE(default_flash_map);
const struct flash_area *flash_map = default_flash_map;
