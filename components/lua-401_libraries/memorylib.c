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
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua-401_port.h"
#include "lua_common.h"

const char *reset_reason[11] = {
        "ESP_RST_UNKNOWN",
        "ESP_RST_POWERON",
        "ESP_RST_EXT",
        "ESP_RST_SW",
        "ESP_RST_PANIC",
        "ESP_RST_INT_WDT",
        "ESP_RST_TASK_WDT",
        "ESP_RST_WDT",
        "ESP_RST_DEEPSLEEP",
        "ESP_RST_BROWNOUT",
        "ESP_RST_SDIO"
};

static int memorylib_minimum_free_heap_size(lua_State *L) {
    lua_pushnumber(L, esp_get_minimum_free_heap_size());
    return 1;
}

static int memorylib_free_heap_size(lua_State *L) {
    lua_pushnumber(L, esp_get_free_heap_size());
    return 1;
}

static int memorylib_reset_reason(lua_State *L) {
    uint8_t format = luaL_check_number(L, 1);
    if (format)
        lua_pushnumber(L, esp_reset_reason());
    else {
        char tp[64];
        memcpy(tp, reset_reason[esp_reset_reason()] + 8, strlen(reset_reason[esp_reset_reason()]) - 7);
        lua_pushstring(L, tp);
    }
    return 1;
}

static int memorylib_tasks_info(lua_State *L) {
    //TaskStatus_t *pxTaskStatusArray;
    //volatile UBaseType_t uxArraySize, x;
    //uint32_t ulTotalRunTime;
    char ptrTaskList[250];

    vTaskList(ptrTaskList);
    printf("----------------------------------------------------\n");
    printf("Task            State   Prio    Stack   Num     Core\n");
    printf("----------------------------------------------------\n");
    printf(ptrTaskList);
    printf("----------------------------------------------------\n");

    /*
    uxArraySize = uxTaskGetNumberOfTasks();
    pxTaskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

    if (pxTaskStatusArray != NULL) {
        uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
        for (x = 0; x < uxArraySize; x++) {
            // TODO: return to LUA pxTaskStatusArray[x].pcTaskName and other parameters
        }
        vPortFree(pxTaskStatusArray);
    }
    */
    return 0;
}

LUALIB_API void lua_memorylibopen(lua_State *L) {
    lua_newtable(L);
    SET_TABLE_FUNCTION("minimum_free_heap_size", memorylib_minimum_free_heap_size);
    SET_TABLE_FUNCTION("free_heap_size"        , memorylib_free_heap_size);
    SET_TABLE_FUNCTION("reset_reason"          , memorylib_reset_reason);
    SET_TABLE_FUNCTION("tasks_info"            , memorylib_tasks_info);
    lua_setglobal(L, "mem");
}
