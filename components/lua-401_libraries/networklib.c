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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif_ip_addr.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua-401_port.h"
#include "tftp_server.h"
#include "wifi.h"
#include "nvs_flash.h"

static int networklib_tftpd_start(lua_State *L) {
    if (!wifi_connected) {
        lua_error(L, "network not connected");
        return 0;
    }
    TFTP_task_start();
    return 0;
}

static int networklib_tftpd_stop(lua_State *L) {
    if (!wifi_connected) {
        lua_error(L, "network not connected");
        return 0;
    }
    TFTP_task_stop();
    return 0;
}

static int networklib_wifi_connect(lua_State *L) {
    size_t len_ssid, len_pass;
    const char *ssid = luaL_check_lstr(L, 1, &len_ssid);
    const char *pass = luaL_check_lstr(L, 2, &len_pass);
    wifi_init_sta(ssid, pass);
    return 0;
}

static int networklib_wifi_disconnect(lua_State *L) {
    if (!wifi_connected) {
        lua_error(L, "network not connected");
        return 0;
    }
    wifi_stop();
    return 0;
}

static int networklib_wifi_scan(lua_State *L) {
    wifi_scan();
    return 0;
}

static int networklib_myip(lua_State *L) {
    if (!wifi_connected) {
        lua_error(L, "network not connected");
        return 0;
    }
    tcpip_adapter_ip_info_t ipInfo;
    char str[256];

    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo);
    sprintf(str, "%d.%d.%d.%d", IP2STR(&ipInfo.ip));
    lua_pushstring(L, str);
    return 1;
}

static const struct luaL_reg esplib[] = {
        { "tftpd_start"    , networklib_tftpd_start     },
        { "tftpd_stop"     , networklib_tftpd_stop      },
        { "wifi_connect"   , networklib_wifi_connect    },
        { "wifi_disconnect", networklib_wifi_disconnect },
        { "wifi_scan"      , networklib_wifi_scan       },
        { "myip"           , networklib_myip            }
};

LUALIB_API void lua_networklibopen(lua_State *L) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    luaL_openl(L, esplib);
}
