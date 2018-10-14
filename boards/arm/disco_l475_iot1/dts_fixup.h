/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */

#define CONFIG_HTS221_NAME			ST_STM32_I2C_V2_40005800_ST_HTS221_5F_LABEL
#define CONFIG_HTS221_I2C_MASTER_DEV_NAME	ST_STM32_I2C_V2_40005800_ST_HTS221_5F_BUS_NAME

#define CONFIG_LIS3MDL_NAME			ST_STM32_I2C_V2_40005800_ST_LIS3MDL_MAGN_1E_LABEL
#define CONFIG_LIS3MDL_I2C_ADDR			ST_STM32_I2C_V2_40005800_ST_LIS3MDL_MAGN_1E_BASE_ADDRESS
#define CONFIG_LIS3MDL_I2C_MASTER_DEV_NAME	ST_STM32_I2C_V2_40005800_ST_LIS3MDL_MAGN_1E_BUS_NAME

#define CONFIG_LSM6DSL_DEV_NAME			ST_STM32_I2C_V2_40005800_ST_LSM6DSL_6A_LABEL
#define CONFIG_LSM6DSL_I2C_ADDR			ST_STM32_I2C_V2_40005800_ST_LSM6DSL_6A_BASE_ADDRESS
#define CONFIG_LSM6DSL_I2C_MASTER_DEV_NAME	ST_STM32_I2C_V2_40005800_ST_LSM6DSL_6A_BUS_NAME

#define CONFIG_LPS22HB_DEV_NAME			ST_STM32_I2C_V2_40005800_ST_LPS22HB_PRESS_5D_LABEL
#define CONFIG_LPS22HB_I2C_ADDR			ST_STM32_I2C_V2_40005800_ST_LPS22HB_PRESS_5D_BASE_ADDRESS
#define CONFIG_LPS22HB_I2C_MASTER_DEV_NAME	ST_STM32_I2C_V2_40005800_ST_LPS22HB_PRESS_5D_BUS_NAME

#define CONFIG_BT_SPI_DEV_NAME			ST_STM32_SPI_FIFO_40003C00_ST_SPBTLE_RF_0_BUS_NAME
#define CONFIG_BT_SPI_MAX_CLK_FREQ		ST_STM32_SPI_FIFO_40003C00_ST_SPBTLE_RF_0_SPI_MAX_FREQUENCY

#define CONFIG_VL53L0X_NAME			ST_STM32_I2C_V2_40005800_ST_VL53L0X_29_LABEL
#define CONFIG_VL53L0X_I2C_ADDR			ST_STM32_I2C_V2_40005800_ST_VL53L0X_29_BASE_ADDRESS
#define CONFIG_VL53L0X_I2C_MASTER_DEV_NAME	ST_STM32_I2C_V2_40005800_ST_VL53L0X_29_BUS_NAME

#define CONFIG_BT_SPI_IRQ_DEV_NAME		BT_IRQ_GPIOS_CONTROLLER
#define CONFIG_BT_SPI_IRQ_PIN			BT_IRQ_GPIOS_PIN
#define CONFIG_BT_SPI_CHIP_SELECT_DEV_NAME	ST_STM32_SPI_FIFO_40003C00_CS_GPIOS_CONTROLLER
#define CONFIG_BT_SPI_CHIP_SELECT_PIN		ST_STM32_SPI_FIFO_40003C00_CS_GPIOS_PIN
#define CONFIG_BT_SPI_RESET_DEV_NAME		BT_RESET_GPIOS_CONTROLLER
#define CONFIG_BT_SPI_RESET_PIN			BT_RESET_GPIOS_PIN
