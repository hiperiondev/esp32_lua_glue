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
#include <string.h>
#include <unistd.h>

#include "lua.h"
#include "lualib.h"
#include "common.h"
#include "lua-401_port.h"

struct Options {
  int toclose;
  int stacksize;
};

void lua_task(void *pvParameter) {
    FS_INIT;
    static lua_State *L = NULL;
    struct Options opt;

    opt.toclose = 0;
    opt.stacksize = 0;
    L = lua_open(opt.stacksize);
    lua_baselibopen(L);
    lua_iolibopen(L);
    lua_strlibopen(L);
    lua_mathlibopen(L);
    lua_dblibopen(L);
    lua_networklibopen(L);
    lua_memorylibopen(L);
    lua_datalib_coreopen(L);
    lua_datalib_arithmeticopen(L);
    lua_datalib_bit_shiftopen(L);
    lua_datalib_bitwise_booleanopen(L);
    lua_datalib_comparisonopen(L);
    lua_datalib_conversionopen(L);
    lua_datalib_date_timeopen(L);
    lua_datalib_mathematicalopen(L);
    lua_datalib_stringopen(L);
    lua_datalib_systemopen(L);
    lua_datalib_validationopen(L);
    l_uart_start();

    char *buffer = NULL;

    lua_dofile(L, "boot.lc");

    while (1) {
#ifdef INTERPRETER
        if (commands_queue) {
            if (uxQueueMessagesWaiting(commands_queue)) {
                if (xQueueReceive(commands_queue, &buffer, (portTickType) portMAX_DELAY)) {
                    lua_dostring(L, buffer);
                }
            }
        }
#endif
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    xTaskCreatePinnedToCore(
            lua_task,
            "LUA Task",
            20000,
            NULL,
            10,
            NULL,
            1
            );
}
