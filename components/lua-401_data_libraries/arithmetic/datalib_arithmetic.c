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
#include <math.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua-401_port.h"
#include "datalib_core.h"
#include "datalib_arithmetic.h"
#include "tracklloc.h"

static int datalib_add(lua_State *L) {
    data_t *data;
    double value = 0, result = 0;

    const int qty = lua_gettop(L);
    if (qty < 2) {
        REMOVE_NIL(qty)
        return 1;
    }

    for (int n = 0; n < qty; n++) {
        NOT_USERDATA(n + 1, qty - n)

        data = (data_t*) lua_touserdata(L, n + 1);
        NOT_ANYMAGNITUDE(data, qty - n - 1)

        GET_VALUE(data, value)
        result += value;
    }

    lua_pushnumber(L, result);
    return 1;
}

static int datalib_mul(lua_State *L) {
    data_t *data;
    double value = 0, result = 1;

    const int qty = lua_gettop(L);
    if (qty < 2) {
        REMOVE_NIL(qty)
        return 1;
    }

    for (int n = 0; n < qty; n++) {
        NOT_USERDATA(n + 1, qty - n)

        data = (data_t*) lua_touserdata(L, n + 1);
        NOT_ANYMAGNITUDE(data, qty - n - 1)

        GET_VALUE(data, value)
        result *= value;
    }

    lua_pushnumber(L, result);
    return 1;
}

static int datalib_sub(lua_State *L) {
    data_t *data1, *data2;
    double value1 = 0, value2 = 0;

    NOT_USERDATA(1, 2)
    data1 = (data_t*) lua_touserdata(L, 1);
    NOT_ANYMAGNITUDE(data1, 2)
    GET_VALUE(data1, value1)

    NOT_USERDATA(2, 2)
    data2 = (data_t*) lua_touserdata(L, 2);
    NOT_ANYMAGNITUDE(data2, 2)
    GET_VALUE(data2, value2)

    lua_pushnumber(L, value1 - value2);
    return 1;
}

static int datalib_div(lua_State *L) {
    data_t *data1, *data2;
    double value1 = 0, value2 = 0;

    NOT_USERDATA(1, 2)
    data1 = (data_t*) lua_touserdata(L, 1);
    NOT_ANYMAGNITUDE(data1, 2)
    GET_VALUE(data1, value1)

    NOT_USERDATA(2, 2)
    data2 = (data_t*) lua_touserdata(L, 2);
    NOT_ANYMAGNITUDE(data2, 2)
    GET_VALUE(data2, value2)

    if (value2 == 0) {
        REMOVE_NIL(2)
        return 1;
    }

    lua_pushnumber(L, value1 / value2);
    return 1;
}

static int datalib_mod(lua_State *L) {
    data_t *data1, *data2;
    double value1 = 0, value2 = 0;

    NOT_USERDATA(1, 2)
    data1 = (data_t*) lua_touserdata(L, 1);
    NOT_ANYINT(data1, 2)
    GET_VALUE(data1, value1)

    NOT_USERDATA(2, 2)
    data2 = (data_t*) lua_touserdata(L, 2);
    NOT_ANYINT(data2, 2)
    GET_VALUE(data2, value2)

    if (value2 == 0) {
        REMOVE_NIL(2)
        return 1;
    }

    lua_pushnumber(L, fmod(value1,value2));
    return 1;
}

static int datalib_expt(lua_State *L) {
    data_t *data1, *data2;
    double value1 = 0, value2 = 0;

    NOT_USERDATA(1, 2)
    data1 = (data_t*) lua_touserdata(L, 1);
    NOT_ANYNUM(data1, 2)
    GET_VALUE(data1, value1)

    NOT_USERDATA(2, 2)
    data2 = (data_t*) lua_touserdata(L, 2);
    NOT_ANYNUM(data2, 2)
    GET_VALUE(data2, value2)

    lua_pushnumber(L, pow(value1, value2));
    return 1;
}

static const struct luaL_reg datalib_arithmetic[] = {
        { "_add"  , datalib_add  },
        { "_mul"  , datalib_mul  },
        { "_sub"  , datalib_sub  },
        { "_div"  , datalib_div  },
        { "_mod"  , datalib_mod  },
        { "_expt" , datalib_expt },
};

LUALIB_API void lua_datalib_arithmeticopen(lua_State *L) {
    luaL_openl(L, datalib_arithmetic);
}
