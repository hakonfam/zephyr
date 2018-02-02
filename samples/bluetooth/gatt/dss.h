/** @file
 *  @brief Data Stream Service sample
 */

/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __cplusplus
extern "C" {
#endif

void dss_init(void);
void dss_stream(u8_t * p_data, size_t len);

#ifdef __cplusplus
}
#endif
