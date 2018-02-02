/** @file
 *  @brief Data Stream Service sample
 */

/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <misc/printk.h>
#include <misc/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

/* Characteristic UUID bb4a1523-ad03-415d-a96c-9d6cddda8304 */
static struct bt_uuid_128 dss_service_uuid = BT_UUID_INIT_128(
	0x04, 0x83, 0xda, 0xdd, 0x6c, 0x9d, 0x6c, 0xa9,
	0x5d, 0x41, 0x03, 0xad, 0x15, 0x23, 0x4a, 0xbb);

/* Characteristic UUID bb4a1524-ad03-415d-a96c-9d6cddda8304 */
static struct bt_uuid_128 dss_data_char_uuid = BT_UUID_INIT_128(
  	0x04, 0x83, 0xda, 0xdd, 0x6c, 0x9d, 0x6c, 0xa9,
  	0x5d, 0x41, 0x03, 0xad, 0x15, 0x24, 0x4a, 0xbb);

/* Characteristic UUID bb4a1525-ad03-415d-a96c-9d6cddda8304 */
static struct bt_uuid_128 dss_rbc_char_uuid = BT_UUID_INIT_128(
  	0x04, 0x83, 0xda, 0xdd, 0x6c, 0x9d, 0x6c, 0xa9,
  	0x5d, 0x41, 0x03, 0xad, 0x15, 0x25, 0x4a, 0xbb);

static struct bt_gatt_ccc_cfg  ds_enable_ccc_cfg[BT_GATT_CCC_MAX] = {};

static u8_t stream_data; // Has receiver enabled data streaming?

static u32_t window_size;

static void ds_enable_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				 u16_t value)
{
	stream_data = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t read_rbc(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			 void *buf, u16_t len, u16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, window_size,
				 sizeof(window_size));
}

static ssize_t write_rbc(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			const void *buf, u16_t len, u16_t offset,
			u8_t flags)
{
  /* The reason this is not implicit behaviour is so that we can reproduce the behaviour you
     get when you use characteristic authorization on the softdevice.

     maybe this interface could be improved so that you could have implicit behaviour
     like that of the softdevice. */
	u8_t *value = attr->user_data;

	if (offset + len > sizeof(ct)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);
	ct_update = 1;

	return len;
}

/* Battery Service Declaration */
static struct bt_gatt_attr dss_attrs[] = {
	BT_GATT_PRIMARY_SERVICE(&dss_service_uuid),

  /* Data characteristic, notification only and CCCD */
	BT_GATT_CHARACTERISTIC(&dss_data_char_uuid, BT_GATT_CHRC_NOTIFY),
	BT_GATT_DESCRIPTOR(&dss_data_char_uuid, BT_GATT_PERM_NONE,
			   NULL, NULL, NULL),
	BT_GATT_CCC(ds_enable_ccc_cfg, ds_enable_ccc_cfg_changed),

  /* Read bytes count characteristic, read write */
  BT_GATT_CHARACTERISTIC(&dss_rbc_char_uuid,
            BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE),
  BT_GATT_DESCRIPTOR(&dss_rbc_char_uuid,
            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
         read_rbc, write_rbc, &window_size),
};

static struct bt_gatt_service dss_svc = BT_GATT_SERVICE(dss_attrs);

void dss_init(void)
{
	bt_gatt_service_register(&dss_svc);
}

void dss_stream(u8_t * p_data, size_t len)
{
  /* check if notifications has been enabled */
	if (!stream_data) {
		return;
	}

	bt_gatt_notify(NULL, &attrs[2], p_data, len);
}
