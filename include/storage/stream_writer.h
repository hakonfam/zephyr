/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for streamed writes
 */

#ifndef ZEPHYR_INCLUDE_STORAGE_STREAM_WRITER_H_
#define ZEPHYR_INCLUDE_STORAGE_STREAM_WRITER_H_

/**
 * @brief Abstraction over buffered stream writes.
 *
 * @defgroup stream_writer Stream sbw
 * @{
 */

#include <stdbool.h>
#include <drivers/flash.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*stream_writer_read_cb_t)(u8_t *buf, size_t len, size_t offset);

typedef int (*stream_writer_write_cb_t)(u8_t *buf, size_t len, size_t offset);

/**
 * @typedef fsw_callback_t
 *
 * @brief Signature for callback invoked after flash write completes.
 *
 * @details Functions of this type are invoked with a buffer containing
 * data read back from the flash after a flash write has completed.
 * This enables verifying that the data has been correctly stored (for
 * instance by using a SHA function). The write buffer 'buf' provided in
 * fsw_init is used as a read buffer for this purpose.
 *
 * @param buf Pointer to the data read.
 * @param len The length of the data read.
 * @param offset The offset the data was read from.
 */
typedef int (*stream_writer_write_done_cb_t)(u8_t *buf, size_t len, size_t offset);

/**
 * @brief Structure for flash buffered writes
 *
 * Users should treat these structures as opaque values and only interact
 * with them through the below API.
 */
struct stream_writer_ctx {
	u8_t *buf; /* Write buffer */
	size_t buf_len; /* Length of write buffer */
	size_t buf_bytes; /* Number of bytes currently stored in write buf */
	size_t bytes_written; /* Number of bytes written to flash */
	stream_writer_write_cb_t write;
	stream_writer_read_cb_t read;
	stream_writer_write_done_cb_t write_done;
};

/**
 * @brief Initialize context needed for stream write API
 *
 * @param ctx context to be initialized
 * @param buf Write buffer
 * @param buf_len Length of write buffer. Can not be larger than the page size
 * @param read Callback to be invoked on 
 * @param write Callback to be invoked on 
 * @param validate Callback to be invoked on 
 *
 * @return non-negative on success, negative errno code on fail
 */
int stream_writer_init(struct sw_ctx *ctx, u8_t *buf, size_t buf_len,
		       stream_writer_read_cb_t read,
		       stream_writer_write_cb_t write,
		       stream_writer_validate_cb_t validate)

/**
 * @brief Read number of bytes written to stream.
 *
 * @note api-tags: pre-kernel-ok isr-ok
 *
 * @param ctx context
 *
 * @return Number of bytes written to stream.
 */
size_t stream_writer_bytes_written(struct sw_ctx *ctx);

/**
 * @brief  Process input buffers to be written to stream in single blocks.
 * Will store remainder between calls.
 *
 * A final call to this function with flush set to true
 * will write out the remaining block buffer to stream.
 *
 * @param ctx context
 * @param data data to write
 * @param len Number of bytes to write
 * @param flush when true this forces any buffered data to be written to flash
 *
 * @return non-negative on success, negative errno code on fail
 */
int stream_writer_buffered_write(struct sw_ctx *ctx, const u8_t *data,
				 size_t len, bool flush)

/**
 * @brief  Process input buffers to be written to stream directly.
 *
 * @param ctx context
 * @param data data to write
 * @param len Number of bytes to write
 *
 * @return non-negative on success, negative errno code on fail
 */
int stream_writer_write(struct sw_ctx *ctx, const u8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ZEPHYR_INCLUDE_STORAGE_STREAM_WRITER_H_ */
