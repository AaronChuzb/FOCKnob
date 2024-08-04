/*
 * @Date: 2024-08-02 22:32:55
 * @LastEditors: AaronChu
 * @LastEditTime: 2024-08-03 17:07:10
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



void foc_init();
void foc1_init();

#ifdef __cplusplus
}
#endif

