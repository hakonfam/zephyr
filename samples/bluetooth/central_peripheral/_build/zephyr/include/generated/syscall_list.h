
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef _ZEPHYR_SYSCALL_LIST_H_
#define _ZEPHYR_SYSCALL_LIST_H_

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

enum {
	K_SYSCALL_ADC_DISABLE,
	K_SYSCALL_ADC_ENABLE,
	K_SYSCALL_ADC_READ,
	K_SYSCALL_AIO_CMP_DISABLE,
	K_SYSCALL_AIO_CMP_GET_PENDING_INT,
	K_SYSCALL_COUNTER_GET_PENDING_INT,
	K_SYSCALL_COUNTER_READ,
	K_SYSCALL_COUNTER_START,
	K_SYSCALL_COUNTER_STOP,
	K_SYSCALL_ENTROPY_GET_ENTROPY,
	K_SYSCALL_FLASH_ERASE,
	K_SYSCALL_FLASH_GET_PAGE_COUNT,
	K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX,
	K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS,
	K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE,
	K_SYSCALL_FLASH_READ,
	K_SYSCALL_FLASH_WRITE,
	K_SYSCALL_FLASH_WRITE_PROTECTION_SET,
	K_SYSCALL_GPIO_CONFIG,
	K_SYSCALL_GPIO_DISABLE_CALLBACK,
	K_SYSCALL_GPIO_ENABLE_CALLBACK,
	K_SYSCALL_GPIO_GET_PENDING_INT,
	K_SYSCALL_GPIO_READ,
	K_SYSCALL_GPIO_WRITE,
	K_SYSCALL_I2C_CONFIGURE,
	K_SYSCALL_I2C_TRANSFER,
	K_SYSCALL_IPM_MAX_DATA_SIZE_GET,
	K_SYSCALL_IPM_MAX_ID_VAL_GET,
	K_SYSCALL_IPM_SEND,
	K_SYSCALL_IPM_SET_ENABLED,
	K_SYSCALL_K_ALERT_RECV,
	K_SYSCALL_K_ALERT_SEND,
	K_SYSCALL_K_CURRENT_GET,
	K_SYSCALL_K_IS_PREEMPT_THREAD,
	K_SYSCALL_K_MSGQ_GET,
	K_SYSCALL_K_MSGQ_INIT,
	K_SYSCALL_K_MSGQ_NUM_FREE_GET,
	K_SYSCALL_K_MSGQ_NUM_USED_GET,
	K_SYSCALL_K_MSGQ_PURGE,
	K_SYSCALL_K_MSGQ_PUT,
	K_SYSCALL_K_MUTEX_INIT,
	K_SYSCALL_K_MUTEX_LOCK,
	K_SYSCALL_K_MUTEX_UNLOCK,
	K_SYSCALL_K_OBJECT_ACCESS_GRANT,
	K_SYSCALL_K_OBJECT_ACCESS_REVOKE,
	K_SYSCALL_K_PIPE_GET,
	K_SYSCALL_K_PIPE_INIT,
	K_SYSCALL_K_PIPE_PUT,
	K_SYSCALL_K_SEM_COUNT_GET,
	K_SYSCALL_K_SEM_GIVE,
	K_SYSCALL_K_SEM_INIT,
	K_SYSCALL_K_SEM_RESET,
	K_SYSCALL_K_SEM_TAKE,
	K_SYSCALL_K_SLEEP,
	K_SYSCALL_K_STACK_INIT,
	K_SYSCALL_K_STACK_POP,
	K_SYSCALL_K_STACK_PUSH,
	K_SYSCALL_K_STR_OUT,
	K_SYSCALL_K_THREAD_ABORT,
	K_SYSCALL_K_THREAD_CANCEL,
	K_SYSCALL_K_THREAD_CREATE,
	K_SYSCALL_K_THREAD_CUSTOM_DATA_GET,
	K_SYSCALL_K_THREAD_CUSTOM_DATA_SET,
	K_SYSCALL_K_THREAD_PRIORITY_GET,
	K_SYSCALL_K_THREAD_PRIORITY_SET,
	K_SYSCALL_K_THREAD_RESUME,
	K_SYSCALL_K_THREAD_START,
	K_SYSCALL_K_THREAD_SUSPEND,
	K_SYSCALL_K_TIMER_REMAINING_GET,
	K_SYSCALL_K_TIMER_START,
	K_SYSCALL_K_TIMER_STATUS_GET,
	K_SYSCALL_K_TIMER_STATUS_SYNC,
	K_SYSCALL_K_TIMER_STOP,
	K_SYSCALL_K_TIMER_USER_DATA_GET,
	K_SYSCALL_K_TIMER_USER_DATA_SET,
	K_SYSCALL_K_UPTIME_GET,
	K_SYSCALL_K_UPTIME_GET_32,
	K_SYSCALL_K_WAKEUP,
	K_SYSCALL_K_YIELD,
	K_SYSCALL_PINMUX_PIN_GET,
	K_SYSCALL_PINMUX_PIN_INPUT_ENABLE,
	K_SYSCALL_PINMUX_PIN_PULLUP,
	K_SYSCALL_PINMUX_PIN_SET,
	K_SYSCALL_PWM_GET_CYCLES_PER_SEC,
	K_SYSCALL_PWM_PIN_SET_CYCLES,
	K_SYSCALL_RTC_DISABLE,
	K_SYSCALL_RTC_ENABLE,
	K_SYSCALL_RTC_GET_PENDING_INT,
	K_SYSCALL_RTC_READ,
	K_SYSCALL_RTC_SET_ALARM,
	K_SYSCALL_SENSOR_ATTR_SET,
	K_SYSCALL_SENSOR_CHANNEL_GET,
	K_SYSCALL_SENSOR_SAMPLE_FETCH,
	K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN,
	K_SYSCALL_SPI_RELEASE,
	K_SYSCALL_SPI_TRANSCEIVE,
	K_SYSCALL_UART_DRV_CMD,
	K_SYSCALL_UART_ERR_CHECK,
	K_SYSCALL_UART_IRQ_ERR_DISABLE,
	K_SYSCALL_UART_IRQ_ERR_ENABLE,
	K_SYSCALL_UART_IRQ_IS_PENDING,
	K_SYSCALL_UART_IRQ_RX_DISABLE,
	K_SYSCALL_UART_IRQ_RX_ENABLE,
	K_SYSCALL_UART_IRQ_TX_DISABLE,
	K_SYSCALL_UART_IRQ_TX_ENABLE,
	K_SYSCALL_UART_IRQ_UPDATE,
	K_SYSCALL_UART_LINE_CTRL_GET,
	K_SYSCALL_UART_LINE_CTRL_SET,
	K_SYSCALL_UART_POLL_IN,
	K_SYSCALL_UART_POLL_OUT,
	K_SYSCALL_BAD,
	K_SYSCALL_LIMIT
};


extern u32_t _handler_counter_start(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_counter_stop(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_counter_read(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_counter_get_pending_int(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_i2c_configure(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_i2c_transfer(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_err_check(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_poll_in(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_poll_out(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_tx_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_tx_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_rx_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_rx_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_err_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_err_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_is_pending(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_irq_update(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_line_ctrl_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_line_ctrl_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_uart_drv_cmd(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_read(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_write(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_erase(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_write_protection_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_get_page_info_by_offs(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_get_page_info_by_idx(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_get_page_count(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_flash_get_write_block_size(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_entropy_get_entropy(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_adc_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_adc_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_adc_read(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_ipm_send(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_ipm_max_data_size_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_ipm_max_id_val_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_ipm_set_enabled(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_rtc_read(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_rtc_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_rtc_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_rtc_set_alarm(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_rtc_get_pending_int(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_object_access_grant(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_object_access_revoke(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_create(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sleep(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_yield(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_wakeup(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_current_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_cancel(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_abort(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_start(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_priority_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_priority_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_suspend(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_resume(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_is_preempt_thread(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_custom_data_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_thread_custom_data_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_start(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_stop(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_status_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_status_sync(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_remaining_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_user_data_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_timer_user_data_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_uptime_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_uptime_get_32(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_stack_init(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_stack_push(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_stack_pop(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_mutex_init(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_mutex_lock(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_mutex_unlock(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sem_init(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sem_take(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sem_give(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sem_reset(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_sem_count_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_alert_recv(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_alert_send(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_init(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_put(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_purge(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_num_free_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_msgq_num_used_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_pipe_init(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_pipe_put(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_pipe_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_k_str_out(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_spi_transceive(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_spi_release(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pinmux_pin_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pinmux_pin_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pinmux_pin_pullup(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pinmux_pin_input_enable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pwm_pin_set_cycles(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_pwm_get_cycles_per_sec(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_sensor_attr_set(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_sensor_sample_fetch(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_sensor_sample_fetch_chan(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_sensor_channel_get(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_config(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_write(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_read(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_enable_callback(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_disable_callback(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_gpio_get_pending_int(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_aio_cmp_disable(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);

extern u32_t _handler_aio_cmp_get_pending_int(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);


#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* _ZEPHYR_SYSCALL_LIST_H_ */
