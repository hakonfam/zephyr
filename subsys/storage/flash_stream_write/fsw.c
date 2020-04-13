/*
 * Copyright (c) 2017, 2020 Nordic Semiconductor ASA
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME FSW
#define LOG_LEVEL CONFIG_FSW_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME, CONFIG_FSW_LOG_LEVEL);

#include <zephyr/types.h>
#include <string.h>
#include <drivers/flash.h>

#include <storage/fsw.h>

#ifdef CONFIG_FSW_ERASE

int fsw_erase_page(struct fsw_ctx *ctx, off_t off)
{
	int rc;
	struct flash_pages_info page;

	rc = flash_get_page_info_by_offs(ctx->fdev, off, &page);
	if (rc != 0) {
		LOG_ERR("Error %d while getting page info", rc);
		return rc;
	}

	if (ctx->last_erased_page_start_offset == page.start_offset) {
		return 0;
	}

	ctx->last_erased_page_start_offset = page.start_offset;
	LOG_INF("Erasing page at offset 0x%08lx", (long)page.start_offset);

	flash_write_protection_set(ctx->fdev, false);
	rc = flash_erase(ctx->fdev, page.start_offset, page.size);
	flash_write_protection_set(ctx->fdev, true);

	if (rc != 0) {
		LOG_ERR("Error %d while erasing page", rc);
	}

	return rc;
}

#endif /* CONFIG_FSW_ERASE */

static int write(struct stream_writer_ctx *ctx, size_t write_offset, size_t len)
{
	int rc = 0;
	struct fsw_ctx fsw = (struct fsw_ctx *)ctx->backend_ctx;
	size_t write_addr = fsw->offset + write_offset;

	if (stream_writer_bytes_written(ctx) + len > ctx->available) {
		return -ENOMEM;
	}

	if (IS_ENABLED(CONFIG_FSW_ERASE)) {
		rc = fsw_erase_page(ctx, write_addr + len - 1);
		if (rc < 0) {
			LOG_ERR("fsw_erase_page error %d offset=0x%08zx", rc,
					write_addr);
			return rc;
		}
	}

	flash_write_protection_set(ctx->fdev, false);
	rc = flash_write(ctx->fdev, write_addr, ctx->buf, len);
	flash_write_protection_set(ctx->fdev, true);

	if (rc != 0) {
		LOG_ERR("flash_write error %d offset=0x%08zx", rc, write_addr);
		return rc;
	}

	return rc;
}

static int read(struct stream_writer_ctx *ctx, size_t read_addr, size_t len,
		u8_t *buf)
{
	struct fsw_ctx fsw = (struct fsw_ctx *)ctx->backend_ctx;

	return flash_read(fsw->fdev, write_addr, buf, len);
}

#ifndef CONFIG_FSW_ERASE
int fsw_write(struct fsw_ctx *ctx, const u8_t *data, size_t len)
{
	stream_writer_write(ctx->stream, data, len);

	return rc;
}
#endif

int fsw_buffered_write(struct fsw_ctx *ctx, const u8_t *data, size_t len,
		       bool flush)
{
	stream_writer_buffered_write(ctx->stream, data, len, flush);

	return rc;
}

size_t fsw_bytes_written(struct fsw_ctx *ctx)
{
	return stream_writer_bytes_written(ctx->stream);
}

int fsw_init(struct fsw_ctx *ctx, struct device *fdev, u8_t *buf,
	     size_t buf_len, size_t offset, size_t size,
	     stream_writer_validate_cb_t validate)
{
	if (!ctx || !fdev) {
		return -EFAULT;
	}

	size_t layout_size = 0;
	size_t total_size = 0;
	const struct flash_pages_layout *layout;
	const struct flash_driver_api *api = fdev->driver_api;

	/* Calculate the total size of the flash device */
	api->page_layout(fdev, &layout, &layout_size);
	for (int i = 0; i < layout_size; i++) {

		total_size += layout->pages_count * layout->pages_size;

		if (buf_len > layout->pages_size) {
			LOG_ERR("Buffer size is bigger than page");
			return -EFAULT;
		}

		layout++;

	}

	if ((offset + size) > total_size ||
	    offset % api->write_block_size) {
		LOG_ERR("Incorrect parameter");
		return -EFAULT;
	}

	ctx->fdev = fdev;
	ctx->offset = offset;
	ctx->available = (size == 0 ? total_size - offset : size);

#ifdef CONFIG_FSW_ERASE
	ctx->last_erased_page_start_offset = -1;
#endif

	return stream_writer_init(&ctx->stream, &ctx, buf, buf_len, read, write,
				  validate);

	return rc;
}
