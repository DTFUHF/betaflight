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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#include "common/axis.h"
#include "common/color.h"
#include "common/maths.h"
#include "common/printf.h"

#include "drivers/nvic.h"

#include "drivers/sensor.h"
#include "drivers/system.h"
#include "drivers/dma.h"
#include "drivers/gpio.h"
#include "drivers/light_led.h"
#include "drivers/sound_beeper.h"
#include "drivers/timer.h"
#include "drivers/serial.h"
#include "drivers/serial_softserial.h"
#include "drivers/serial_uart.h"
#include "drivers/accgyro.h"
#include "drivers/compass.h"
#include "drivers/pwm_output.h"
#include "drivers/adc.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_spi.h"
#include "drivers/inverter.h"
#include "drivers/flash_m25p16.h"
#include "drivers/sonar_hcsr04.h"
#include "drivers/sdcard.h"
#include "drivers/usb_io.h"
#include "drivers/transponder_ir.h"
#include "drivers/io.h"
#include "drivers/exti.h"
#include "drivers/vtx_soft_spi_rtc6705.h"

#ifdef USE_BST
#include "bus_bst.h"
#endif

#include "rx/rx.h"
#include "rx/spektrum.h"

#include "io/beeper.h"
#include "io/serial.h"
#include "io/flashfs.h"
#include "io/gps.h"
#include "io/gimbal.h"
#include "io/ledstrip.h"
#include "io/asyncfatfs/asyncfatfs.h"
#include "io/transponder_ir.h"
#include "io/osd.h"
#include "io/vtx.h"

#include "scheduler/scheduler.h"

#include "sensors/sensors.h"
#include "sensors/sonar.h"
#include "sensors/barometer.h"
#include "sensors/compass.h"
#include "sensors/acceleration.h"
#include "sensors/gyro.h"
#include "sensors/battery.h"
#include "sensors/boardalignment.h"
#include "sensors/initialisation.h"

#include "telemetry/telemetry.h"
#include "blackbox/blackbox.h"

#include "flight/pid.h"
#include "flight/imu.h"
#include "flight/mixer.h"
#include "flight/failsafe.h"
#include "flight/navigation.h"

#include "config/config_profile.h"
#include "config/config_master.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    { TIM5,  IO_TAG(PA3), TIM_Channel_4, TIM_USE_PPM,   0, GPIO_AF_TIM5,  NULL,  0, 0, }, // PPM_IN
    { TIM8,  IO_TAG(PC9), TIM_Channel_4, TIM_USE_MOTOR, 1, GPIO_AF_TIM8,  NULL, 0, 0}, // S1_OUT
    { TIM8,  IO_TAG(PC8), TIM_Channel_3, TIM_USE_MOTOR, 1, GPIO_AF_TIM8,  NULL, 0, 0}, // S2_OUT
    { TIM14, IO_TAG(PA7), TIM_Channel_1, TIM_USE_MOTOR, 1, GPIO_AF_TIM14, NULL, 0, 0}, // S3_OUT
    { TIM3,  IO_TAG(PB4), TIM_Channel_1, TIM_USE_MOTOR, 1, GPIO_AF_TIM3,  NULL, 0, 0}, // S4_OUT
    { TIM3,  IO_TAG(PB0), TIM_Channel_3, TIM_USE_MOTOR, 1, GPIO_AF_TIM3,  NULL, 0, 0}, // S5_OUT
    { TIM3,  IO_TAG(PB1), TIM_Channel_4, TIM_USE_MOTOR, 1, GPIO_AF_TIM3,  NULL, 0, 0}, // S6_OUT
    { TIM5,  IO_TAG(PA0), TIM_Channel_1, TIM_USE_MOTOR, 1, GPIO_AF_TIM5,  NULL, 0, 0}, // S7_OUT
    { TIM5,  IO_TAG(PA1), TIM_Channel_2, TIM_USE_MOTOR, 1, GPIO_AF_TIM5,  NULL, 0, 0}, // S8_OUT
};


/*
const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM5,  CH4, PA3, TIM_USE_PPM,   TIMER_OUTPUT_NONE,     0),
    DEF_TIM(TIM8,  CH4, PC9, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM8,  CH3, PC8, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM14, CH1, PA7, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM3,  CH1, PB4, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM3,  CH3, PB0, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM3,  CH4, PB1, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM5,  CH1, PA0, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
    DEF_TIM(TIM5,  CH2, PA1, TIM_USE_MOTOR, TIMER_OUTPUT_STANDARD, 0),
};
*/

