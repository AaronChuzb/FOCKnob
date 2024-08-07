/*
 * @Date: 2024-08-02 22:32:55
 * @LastEditors: AaronChu
 * @LastEditTime: 2024-08-07 22:56:33
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
#include "esp_check.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "iot_button.h"

#include "tusb.h"
#include "esp_private/usb_phy.h"
#include <inttypes.h>

#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "lv_demos.h"

/* LCD size */
#define EXAMPLE_LCD_H_RES   (240)
#define EXAMPLE_LCD_V_RES   (240)

/* LCD settings */
#define EXAMPLE_LCD_SPI_NUM         (SPI2_HOST)
#define EXAMPLE_LCD_PIXEL_CLK_HZ    (40 * 1000 * 1000)
#define EXAMPLE_LCD_CMD_BITS        (8)
#define EXAMPLE_LCD_PARAM_BITS      (8)
#define EXAMPLE_LCD_COLOR_SPACE     ESP_LCD_COLOR_SPACE_BGR
#define EXAMPLE_LCD_BITS_PER_PIXEL  (16)
#define EXAMPLE_LCD_DRAW_BUFF_DOUBLE (1)
#define EXAMPLE_LCD_DRAW_BUFF_HEIGHT (50)

/* LCD pins */
#define EXAMPLE_LCD_GPIO_SCLK       (GPIO_NUM_12)
#define EXAMPLE_LCD_GPIO_MOSI       (GPIO_NUM_11)
#define EXAMPLE_LCD_GPIO_RST        (GPIO_NUM_9)
#define EXAMPLE_LCD_GPIO_DC         (GPIO_NUM_14)
#define EXAMPLE_LCD_GPIO_CS         (GPIO_NUM_10)
#define EXAMPLE_LCD_GPIO_BL         (GPIO_NUM_13)

#define LEDC_TIMER              LEDC_TIMER_1
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          EXAMPLE_LCD_GPIO_BL // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_4
#define LEDC_DUTY_RES           LEDC_TIMER_10_BIT // Set duty resolution to 10 bits
#define LEDC_DUTY               (512) // Set duty to 50%. (2 ** 10) * 50% = 512
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz

#define PHASE_U_GPIO 15
#define PHASE_V_GPIO 16
#define PHASE_W_GPIO 17
#define MOTOR_PP     7
#define MT6701_SPI_HOST SPI3_HOST
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


void lvgl_display_init(void);
void display_init(void);

void foc_init();
void foc1_init();

void surface_dial_report(uint8_t key);
void surface_dial_init();

#ifdef __cplusplus
}
#endif

