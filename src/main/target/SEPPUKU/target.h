/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>

#define TARGET_BOARD_IDENTIFIER "SEPPUKU"

#define CONFIG_START_FLASH_ADDRESS (0x08010000) // 64kB, flash sector

#define USBD_PRODUCT_STRING     "Seppuku"

#define IDLE_COUNTS_PER_SEC_AT_NO_LOAD (16564455)

#define LED0                    PC14

#define VIDEO_VSYNC          PB12
#define VIDEO_HSYNC          PA15

#define USE_EXTI
#define GYRO
#define ACC

#define USE_ACCGYRO_BMI160
#define GYRO_BMI160_ALIGN    CW0_DEG
#define ACC_BMI160_ALIGN     CW0_DEG
#define BMI160_SPI_INSTANCE  SPI3
#define BMI160_SPI_DIVISOR   16
#define BMI160_CS_PIN        PD2
#define BMI160_INT_EXTI      PC4

#define USABLE_TIMER_CHANNEL_COUNT 9
#define USED_TIMERS  ( TIM_N(3) | TIM_N(5) | TIM_N(8) | TIM_N(14) )

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

// required by highend source for cms ???
// hopefully doesnt fuck shit up
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define M25P16_SPI_SHARED
#define M25P16_CS_PIN           PD2
#define M25P16_SPI_INSTANCE     SPI3

#define OSD

#define USE_VCP
#define VBUS_SENSING_PIN        PB8
#define VBUS_SENSING_ENABLED

#define SERIAL_PORT_COUNT       2 //VCP, USART6

#define USE_SPI

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN            PC10
#define SPI3_MISO_PIN           PC11
#define SPI3_MOSI_PIN           PC12

#define DEFAULT_RX_FEATURE      FEATURE_RX_PPM


#define SPEKTRUM_BIND
#define BIND_PIN                PC5

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff

