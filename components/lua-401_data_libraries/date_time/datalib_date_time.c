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

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua-401_port.h"
#include "datalib_core.h"
#include "datalib_date_time.h"

static int datalib_add_dt_time(lua_State *L) {
    return 0;
}

static int datalib_add_tod_time(lua_State *L) {
    return 0;
}

static int datalib_add_time(lua_State *L) {
    return 0;
}

static int datalib_concat_date_tod(lua_State *L) {
    return 0;
}

static int datalib_concat_date(lua_State *L) {
    return 0;
}

static int datalib_concat_dt(lua_State *L) {
    return 0;
}

static int datalib_concat_tod(lua_State *L) {
    return 0;
}

static int datalib_day_of_week(lua_State *L) {
    return 0;
}

static int datalib_divtime(lua_State *L) {
    return 0;
}

static int datalib_multime(lua_State *L) {
    return 0;
}

static int datalib_split_date(lua_State *L) {
    return 0;
}

static int datalib_split_dt(lua_State *L) {
    return 0;
}

static int datalib_split_tod(lua_State *L) {
    return 0;
}

static int datalib_sub_date_date(lua_State *L) {
    return 0;
}

static int datalib_sub_dt_dt(lua_State *L) {
    return 0;
}

static int datalib_sub_dt_time(lua_State *L) {
    return 0;
}

static int datalib_sub_tod_tod(lua_State *L) {
    return 0;
}

static int datalib_sub_tod_time(lua_State *L) {
    return 0;
}

static int datalib_sub_time(lua_State *L) {
    return 0;
}

LUALIB_API void lua_datalib_date_timeopen(lua_State *L) {
    lua_getglobal(L, "var");
    SET_TABLE_FUNCTION("add_dt_time"    , datalib_add_dt_time);
    SET_TABLE_FUNCTION("add_tod_time"   , datalib_add_tod_time);
    SET_TABLE_FUNCTION("add_time"       , datalib_add_time);
    SET_TABLE_FUNCTION("concat_date_tod", datalib_concat_date_tod);
    SET_TABLE_FUNCTION("concat_date"    , datalib_concat_date);
    SET_TABLE_FUNCTION("concat_dt"      , datalib_concat_dt);
    SET_TABLE_FUNCTION("concat_tod"     , datalib_concat_tod);
    SET_TABLE_FUNCTION("day_of_week"    , datalib_day_of_week);
    SET_TABLE_FUNCTION("divtime"        , datalib_divtime);
    SET_TABLE_FUNCTION("multime"        , datalib_multime);
    SET_TABLE_FUNCTION("split_date"     , datalib_split_date);
    SET_TABLE_FUNCTION("split_dt"       , datalib_split_dt);
    SET_TABLE_FUNCTION("split_tod"      , datalib_split_tod);
    SET_TABLE_FUNCTION("sub_date_date"  , datalib_sub_date_date);
    SET_TABLE_FUNCTION("sub_dt_dt"      , datalib_sub_dt_dt);
    SET_TABLE_FUNCTION("sub_dt_time"    , datalib_sub_dt_time);
    SET_TABLE_FUNCTION("sub_tod_tod"    , datalib_sub_tod_tod);
    SET_TABLE_FUNCTION("sub_tod_time"   , datalib_sub_tod_time);
    SET_TABLE_FUNCTION("sub_time"       , datalib_sub_time);
    lua_setglobal(L, "var");
}
