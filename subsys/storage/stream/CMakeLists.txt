#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#

zephyr_sources_ifdef(CONFIG_STORAGE_STREAM stream.c)
zephyr_include_directories_ifdef(CONFIG_STORAGE_STREAM include)

zephyr_sources_ifdef(CONFIG_STREAM_FLASH stream_flash.c)
