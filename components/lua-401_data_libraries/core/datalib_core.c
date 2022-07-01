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
#include "tracklloc.h"

int types_tags[DATA_TYPES_QTY] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const char *types_name[DATA_TYPES_QTY] = {
    EP(DATA_TYPE_NULL),
    EP(DATA_TYPE_BOOL),
    EP(DATA_TYPE_SINT),
    EP(DATA_TYPE_INT),
    EP(DATA_TYPE_DINT),
    EP(DATA_TYPE_LINT),
    EP(DATA_TYPE_USINT),
    EP(DATA_TYPE_UINT),
    EP(DATA_TYPE_UDINT),
    EP(DATA_TYPE_ULINT),
    EP(DATA_TYPE_REAL),
    EP(DATA_TYPE_LREAL),
    EP(DATA_TYPE_TIME),
    EP(DATA_TYPE_DATE),
    EP(DATA_TYPE_TOD),
    EP(DATA_TYPE_DT),
    EP(DATA_TYPE_STRING),
    EP(DATA_TYPE_WSTRING),
    EP(DATA_TYPE_POINTER),
    EP(DATA_TYPE_TABLE),
    EP(DATA_TYPE_USER)
};

static void strupp(char *beg) {
    while ((*beg++ = toupper(*beg)))
        ;
}

static int datalib_var_get(lua_State *L) {
    data_t *data = lua_touserdata(L, 1);
    const char *i = luaL_check_string(L, 2);

    if (!strcmp(i, "tt")) {
        lua_pushnumber(L, data->tt);
        goto end;
    }

    if (!strcmp(i, "type")) {
        lua_pushnumber(L, data->type);
        goto end;
    }

    if (!strcmp(i, "val")) {
        switch (data->type) {
            case DATA_TYPE_NULL:
            case DATA_TYPE_NIL:
                lua_pushnil(L);
                break;

            case DATA_TYPE_BOOL:
                lua_pushnumber(L, data->boolean);
                break;

            case DATA_TYPE_SINT:
                lua_pushnumber(L, data->sint);
                break;

            case DATA_TYPE_INT:
                lua_pushnumber(L, data->intg);
                break;

            case DATA_TYPE_DINT:
                lua_pushnumber(L, data->dint);
                break;

            case DATA_TYPE_USINT:
                lua_pushnumber(L, data->usint);
                break;

            case DATA_TYPE_UINT:
                lua_pushnumber(L, data->uint);
                break;

            case DATA_TYPE_UDINT:
                lua_pushnumber(L, data->udint);
                break;

            case DATA_TYPE_LINT: // TODO: implement
            case DATA_TYPE_ULINT:
                lua_pushnil(L);
                break;

            case DATA_TYPE_REAL: // TODO: implement
                lua_pushnumber(L, data->real);
                break;
            case DATA_TYPE_LREAL: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_TIME: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_DATE: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_TOD: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_DT: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_STRING: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_WSTRING: // TODO: implement
                lua_pushnil(L);
                break;

            case DATA_TYPE_POINTER: // TODO: implement
            case DATA_TYPE_TABLE:
            case DATA_TYPE_USER:
                lua_pushnil(L);
                break;

            default:
                lua_pushnil(L);
        }
    }

    end:
    return 1;
}

static int datalib_var_set(lua_State *L) {
    data_t *data = lua_touserdata(L, 1);
    const char *i = luaL_check_string(L, 2);
    const double t = luaL_check_number(L, 3);
    if (!strcmp(i, "tt")) {
        data->tt = t;
        goto end;
    }

    if (!strcmp(i, "type")) {
        data->type = t;
        goto end;
    }

    if (!strcmp(i, "val")) {
        switch (data->type) {
            case DATA_TYPE_NULL:
            case DATA_TYPE_NIL:
                break;

            case DATA_TYPE_BOOL:
                if (t)
                    data->boolean = true;
                else
                    data->boolean = false;
                break;

            case DATA_TYPE_SINT:
                data->sint = t;
                break;

            case DATA_TYPE_INT:
                data->intg = t;
                break;

            case DATA_TYPE_DINT:
                data->dint = t;
                break;

            case DATA_TYPE_USINT:
                data->usint = t;
                break;

            case DATA_TYPE_UINT:
                data->uint = t;
                break;

            case DATA_TYPE_UDINT:
                data->udint = t;
                break;

            case DATA_TYPE_LINT: // TODO: implement
            case DATA_TYPE_ULINT:
                break;

            case DATA_TYPE_REAL: // TODO: implement
                break;

            case DATA_TYPE_LREAL: // TODO: implement
                break;

            case DATA_TYPE_TIME: // TODO: implement
                break;

            case DATA_TYPE_DATE: // TODO: implement
                break;

            case DATA_TYPE_TOD: // TODO: implement
                break;

            case DATA_TYPE_DT: // TODO: implement
                break;

            case DATA_TYPE_STRING: // TODO: implement
                break;

            case DATA_TYPE_WSTRING: // TODO: implement
                break;

            case DATA_TYPE_POINTER: // TODO: implement
            case DATA_TYPE_TABLE:
            case DATA_TYPE_USER:
                break;

            default:
                break;
        }
    }

    end:
    return 0;
}

/////////////////////

static int datalib_var_new(lua_State *L) {
    uint8_t n, t = 255;
    char tp[64];
    data_t *data;

    char *type = luaL_check_string(L, 1);
    strupp(type);
    for (n = 0; n < DATA_TYPES_QTY; n++) {
        memcpy(tp, types_name[n] + 10, strlen(types_name[n]) - 9);
        if (!strcmp(tp, type)) {
            t = n;
            break;
        }
    }
    if (t == 255) {
        lua_error(L, "unknown type");
        return 0;
    }

    if (types_tags[t] == 0) {
        int xtag = lua_newtag(L);
        types_tags[t] = xtag;
        lua_pushcfunction(L, datalib_var_get);
        lua_settagmethod(L, xtag, "gettable");
        lua_pushcfunction(L, datalib_var_set);
        lua_settagmethod(L, xtag, "settable");
    }

    lua_newuserdata(L, sizeof(data_t));
    lua_settag(L, types_tags[t]);
    data = lua_touserdata(L, -1);

    data->type = t;
    data->tt = DATA_TT_NORMAL;
    data->ulint = 0;

    lua_pushusertag(L, data, types_tags[t]);
    return 1;
}

static int datalib_is_anynum(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_NUM(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anydate(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_DATE(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anybit(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_BIT(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anyreal(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_REAL(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anyint(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_INT(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anystring(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_STRING(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_is_anyelementary(lua_State *L) {
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 1);
        lua_pushnil(L);
        return 1;
    }
    data_t *data = (data_t*) lua_touserdata(L, 1);

    if (ANY_ELEMENTARY(data->type))
        lua_pushnumber(L, 1);
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_getbit(lua_State *L) {
    data_t *data = (data_t*) lua_touserdata(L, 1);
    uint8_t bit = luaL_check_number(L, 2);

    if (ANY_BIT(data->type))
        lua_pushnumber(L, GET_BIT(data->ulint, bit));
    else
        lua_pushnil(L);

    return 1;
}

static int datalib_setbit(lua_State *L) {
    data_t *data = (data_t*) lua_touserdata(L, 1);
    uint8_t bit = luaL_check_number(L, 2);

    if (ANY_BIT(data->type))
        data->ulint = SET_BIT(data->ulint, bit);

    return 0;
}

static int datalib_clearbit(lua_State *L) {
    data_t *data = (data_t*) lua_touserdata(L, 1);
    uint8_t bit = luaL_check_number(L, 2);

    if (ANY_BIT(data->type))
        data->ulint = CLR_BIT(data->ulint, bit);

    return 0;
}

static const struct luaL_reg datalib_core[] = {
        { "var"             , datalib_var_new          },
        { "is_anynum"       , datalib_is_anynum        },
        { "is_anydate"      , datalib_is_anydate       },
        { "is_anybit"       , datalib_is_anybit        },
        { "is_anyreal"      , datalib_is_anyreal       },
        { "is_anyint"       , datalib_is_anyint        },
        { "is_anystring"    , datalib_is_anystring     },
        { "is_anyelementary", datalib_is_anyelementary },
        { "getbit"          , datalib_getbit           },
        { "setbit"          , datalib_setbit           },
        { "clearbit"        , datalib_clearbit         },
};

LUALIB_API void lua_datalib_coreopen(lua_State *L) {
    luaL_openl(L, datalib_core);
}
