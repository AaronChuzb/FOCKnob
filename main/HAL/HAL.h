/*
 * @Date: 2024-08-02 22:32:55
 * @LastEditors: AaronChu
 * @LastEditTime: 2024-08-04 19:52:24
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "iot_button.h"

#include "tusb.h"
#include "esp_private/usb_phy.h"
#include <inttypes.h>

#define PHASE_U_GPIO 15
#define PHASE_V_GPIO 16
#define PHASE_W_GPIO 17
#define MOTOR_PP     7
#define MT6701_SPI_HOST SPI2_HOST
#define MT6701_SPI_SCLK_GPIO 2
#define MT6701_SPI_MISO_GPIO 1
#define MT6701_SPI_MOSI_GPIO -1
#define MT6701_SPI_CS_GPIO 42

#define SWITCH_BUTTON 0


#define USING_MCPWM 0

#if !USING_MCPWM
#define LEDC_CHAN_0 0
#define LEDC_CHAN_1 1
#define LEDC_CHAN_2 2
#endif

#define REPORT_ID    1
#define DIAL_R       0xC8
#define DIAL_L       0x38
#define DIAL_PRESS   0x01
#define DIAL_RELEASE 0x00
#define DIAL_R_F     0x14
#define DIAL_L_F     0xEC



void foc_init();
void foc1_init();

void surface_dial_report(uint8_t key);
void surface_dial_init();

#ifdef __cplusplus
}
#endif

