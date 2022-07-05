/*
 * Copyright 2022 Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/esp32_lua_glue *
 *
 * This is based on other projects:
 *    Lua language (https://www.lua.org/)
 *    LittleFS port for ESP-IDF (https://github.com/joltwallet/esp_littlefs)
 *    Lightweight TFTP server library (https://github.com/lexus2k/libtftp)
 *    Others (see individual files)
 *
 *    please contact their authors for more information.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"

#include "uart.h"

static const char *TAG = "isc_uart_events";

#define EX_UART_NUM UART_NUM_0

#define BUF_SIZE (128)
#define RD_BUF_SIZE (BUF_SIZE)
static QueueHandle_t uart0_queue;
char buff[255];
uint8_t buff_cnt = 0;
static xTaskHandle uart_task_handle = NULL;

static void l_uart_event_task(void *pvParameters) {
    uart_event_t event;
    uint8_t *dtmp = (uint8_t*) malloc(RD_BUF_SIZE);

    uart_write_bytes(EX_UART_NUM, "\n\r >", 4);
    for (;;) {
        if (xQueueReceive(uart0_queue, (void*) &event, (portTickType) portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);

            switch (event.type) {
                case UART_DATA:
                    uart_read_bytes(EX_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    buff[buff_cnt] = dtmp[0];
                    if (buff[buff_cnt] == '\0')
                        break;
                    if (buff[buff_cnt] == 0x0d) {
                        buff[buff_cnt] = '\0';
                        buff_cnt = 0;
                        uart_write_bytes(EX_UART_NUM, "\n\r >", 4);
                        char *pData = buff;
                        xQueueSend(commands_queue, &pData, (TickType_t)0);
                    } else {
                        if (buff_cnt > 253) {
                            break;
                        }
                        uart_write_bytes(EX_UART_NUM, &buff[buff_cnt++], 1);
                    }
                    break;
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(EX_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(EX_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    xQueueReset(uart0_queue);
                    break;
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    xQueueReset(uart0_queue);
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    xQueueReset(uart0_queue);
                    break;
            }
        }
    }

    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

void l_uart_send(char *data) {
    uart_write_bytes(EX_UART_NUM, data, strlen(data));
}

void l_uart_start(void) {
    uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(EX_UART_NUM, &uart_config);
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 100, &uart0_queue, 0);

    commands_queue = xQueueCreate(1, sizeof(char*));

    buff[0] = '\0';
    xTaskCreate(
            l_uart_event_task,
            "uart_event_task",
            1024,
            NULL,
            12,
            &uart_task_handle
            );
}

void l_uart_stop(void) {
    uart_driver_delete(EX_UART_NUM);
    vTaskDelete(uart_task_handle);
}
