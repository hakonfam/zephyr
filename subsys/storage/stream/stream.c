/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME STREAM_WRITER
#define LOG_LEVEL CONFIG_STREAM_WRITER_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME, CONFIG_STREAM_WRITER_LOG_LEVEL);

#include <zephyr/types.h>
#include <string.h>

#include <stream.h>


static int sync(struct sw_ctx *ctx)
{
	int rc = 0;

	rc = ctx->write(ctx, ctx->bytes_written, ctx->buf_bytes);
	if (rc != 0) {
		LOG_ERR("write failed: %d", rc);
		return rc;
	}

	if (ctx->verify) {
		/* Invert to ensure that caller is able to discover a faulty
		 * read callback even if no error code is returned.
		 */
		for (int i = 0; i < ctx->buf_bytes; i++) {
			ctx->buf[i] = ~ctx->buf[i];
		}

		rc = ctx->read(ctx, ctx->bytes_writen, ctx->buf_bytes,
			       ctx->buf);
		if (rc != 0) {
			LOG_ERR("read failed: %d", rc);
			return rc;
		}

		rc = ctx->verify(ctx->buf, ctx->buf_bytes, ctx->bytes_written);
		if (rc != 0) {
			LOG_ERR("verify failed: %d", rc);
		}
	}

	ctx->bytes_written += ctx->buf_bytes;
	ctx->buf_bytes = 0U;

	return rc;
}

int stream_write(struct sw_ctx *ctx, const u8_t *data, size_t len)
{
	if (ctx == NULL || data == NULL) {
		return -EFAULT;
	}

	ctx.buf = data;
	ctx.bytes_writen = len;

	return sync(ctx);

}

int stream_buffered_write(struct sw_ctx *ctx, const u8_t *data,
				 size_t len, bool flush)
{
	int processed = 0;
	int rc = 0;
	int buf_empty_bytes;

	if (ctx->buf == NULL) {
		return -EFAULT;
	}

	if (ctx == NULL || data == NULL) {
		return -EFAULT;
	}

	while ((len - processed) >=
	       (buf_empty_bytes = ctx->buf_len - ctx->buf_bytes)) {
		memcpy(ctx->buf + ctx->buf_bytes, data + processed,
		       buf_empty_bytes);

		ctx->buf_bytes = ctx->buf_len;
		rc = sync(ctx);

		if (rc != 0) {
			return rc;
		}

		processed += buf_empty_bytes;
	}

	/* place rest of the data into ctx->buf */
	if (processed < len) {
		memcpy(ctx->buf + ctx->buf_bytes,
		       data + processed, len - processed);
		ctx->buf_bytes += len - processed;
	}

	if (flush && ctx->buf_bytes > 0) {
		rc = sync(ctx);
	}

	return rc;
}

size_t stream_bytes_written(struct sw_ctx *ctx)
{
	return ctx->bytes_written;
}

int stream_init(struct sw_ctx *ctx, u8_t *buf, size_t buf_len,
		       stream_read_cb_t read,
		       stream_write_cb_t write,
		       stream_validate_cb_t validate)
{
	if (ctx == NULL || write == NULL ||
	    (validate != NULL && read == NULL)) {
		return -EFAULT;
	}

	ctx->buf = buf;
	ctx->buf_len = buf_len;
	ctx->bytes_written = 0;
	ctx->buf_bytes = 0U;
	ctx->read = read;
	ctx->write = write;
	ctx->validate = validate;

	return 0;
}
