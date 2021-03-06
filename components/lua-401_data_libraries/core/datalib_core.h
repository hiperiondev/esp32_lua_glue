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

#ifndef DATA_H_
#define DATA_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define DATA_TYPES_QTY 21
#define DATA_TT_QTY    4
#define EP(x) [x] = #x

extern const char *types_name[DATA_TYPES_QTY];
extern const char *types_tt[DATA_TT_QTY];
extern int types_tags[DATA_TYPES_QTY];

// data types
typedef enum {
    DATA_TYPE_NULL    = 0x00,  //
    DATA_TYPE_BOOL    = 0x01,  // bool
    DATA_TYPE_SINT    = 0x02,  // int8_t
    DATA_TYPE_INT     = 0x03,  // int16_t
    DATA_TYPE_DINT    = 0x04,  // int32_t
    DATA_TYPE_LINT    = 0x05,  // int64_t
    DATA_TYPE_USINT   = 0x06,  // uint8_t
    DATA_TYPE_UINT    = 0x07,  // uint16_t
    DATA_TYPE_UDINT   = 0x08,  // uint32_t
    DATA_TYPE_ULINT   = 0x09,  // uint64_t
    DATA_TYPE_REAL    = 0x0a,  // float
    DATA_TYPE_LREAL   = 0x0b,  // double
    DATA_TYPE_TIME    = 0x0c,  // time_t
    DATA_TYPE_DATE    = 0x0d,  // date_t
    DATA_TYPE_TOD     = 0x0e,  // tod_t
    DATA_TYPE_DT      = 0x0f,  // dat_t
    DATA_TYPE_STRING  = 0x10,  // char
    DATA_TYPE_WSTRING = 0x11,  // wchar_t
    DATA_TYPE_POINTER = 0x12,  // pointer_t
    DATA_TYPE_TABLE   = 0x13,  // table_t
    DATA_TYPE_USER    = 0x14,  // user_t
    DATA_TYPE_NDEF_15 = 0x15,  // not defined
    DATA_TYPE_NDEF_16 = 0x16,  // not defined
    DATA_TYPE_NDEF_17 = 0x17,  // not defined
    DATA_TYPE_NDEF_18 = 0x18,  // not defined
    DATA_TYPE_NDEF_19 = 0x19,  // not defined
    DATA_TYPE_NDEF_1A = 0x1a,  // not defined
    DATA_TYPE_NDEF_1B = 0x1b,  // not defined
    DATA_TYPE_NDEF_1C = 0x1c,  // not defined
    DATA_TYPE_NDEF_1D = 0x1d,  // not defined
    DATA_TYPE_NDEF_1E = 0x1e,  // not defined
    DATA_TYPE_NIL     = 0x1f,  // nil
} vartype_t;

typedef enum {
    DATA_TT_MARK    = 0x00,
    DATA_TT_NORMAL  = 0x01,
    DATA_TT_PERSIST = 0x02,
    DATA_TT_RETAIN  = 0x03,
} tt_t;

typedef union {
    struct {
         uint8_t day;
         uint8_t month;
        uint16_t year;
    } date;
        uint32_t dw_date;
} date_t;

typedef union {
    struct {
        uint8_t csec;
        uint8_t sec;
        uint8_t min;
        uint8_t hour;
    } tod;
       uint32_t dw_tod;
} tod_t;

typedef struct {
    struct {
         tod_t tod;
        date_t date;
    } dat;
      uint64_t dw_dat;
} dat_t;

typedef uint64_t pointer_t;

typedef struct {
        void *data;
    uint64_t value;
} user_t;

typedef struct {
        bool wstring;
    uint32_t len;
    uint32_t hash;
    union {
           char *str;
        wchar_t *wstr;
    };
} string_t;

typedef struct {
      uint64_t len;
          void *table;
} table_t;

typedef struct {
        vartype_t type;
             tt_t tt;
    union {
             bool boolean;
           int8_t sint;
          int16_t intg;
          int32_t dint;
          int64_t lint;
          uint8_t usint;
         uint16_t uint;
         uint32_t udint;
         uint64_t ulint;
            float real;
           double lreal;
           time_t time;
           date_t date;
            tod_t tod;
            dat_t dt;
         string_t *string;
         uint64_t pointer;
          table_t table;
           user_t user;
         uint16_t *code;
    };
} data_t;

#define ANY_NUM(x)               (x < 0x0c)
#define ANY_DATE(x)              (x == DATA_TYPE_DATE || x == DATA_TYPE_TOD || x == DATA_TYPE_DT)
#define ANY_BIT(x)               (x == DATA_TYPE_BOOL || x == DATA_TYPE_UINT || x == DATA_TYPE_UDINT || x == DATA_TYPE_ULINT)
#define ANY_REAL(x)              (x == DATA_TYPE_REAL || x == DATA_TYPE_LREAL)
#define ANY_STRING(x)            (x == DATA_TYPE_STRING || x == DATA_TYPE_WSTRING)
#define ANY_ELEMENTARY(x)        (ANY_BIT(x) || ANY_NUM(x) || ANY_DATE(x) || ANY_STRING(x) || x == DATA_TYPE_TIME)
#define ANY_MAGNITUDE(x)         ((x < 0x0d) && !(x == DATA_TYPE_NULL))
#define ANY_INT(x)               ((x < 0x0a) && !(x == DATA_TYPE_NULL))
#define ANY_INTEGRAL(x)          (ANY_INT(x) || ANY_BIT(x))

#define GET_BIT(v, b)            ((v >> b) & 1)
#define SET_BIT(v, b)            ((v) | (1 << b))
#define CLR_BIT(v, b)            ((v) & ~(1 << b))

#define REMOVE_NIL(qty) \
		lua_remove(L, qty); \
		lua_pushnil(L);

#define NOT_USERDATA(pos, qty) \
		if (!lua_isuserdata(L, pos)) { \
			REMOVE_NIL(qty) \
		    return 1; \
		}

#define NOT_ANYMAGNITUDE(data, qty) \
        if (!ANY_MAGNITUDE(data->type)) { \
        	REMOVE_NIL(qty) \
            return 1; \
        }

#define NOT_ANYINT(data, qty) \
        if (!ANY_INT(data->type)) { \
            REMOVE_NIL(qty) \
            return 1; \
        }

#define NOT_ANYNUM(data, qty) \
        if (!ANY_NUM(data->type)) { \
            REMOVE_NIL(qty) \
            return 1; \
        }

#define GET_VALUE(data, value) \
		switch (data->type) { \
		        case DATA_TYPE_BOOL: \
		            value = data->boolean; \
		            break; \
		        case DATA_TYPE_SINT: \
		            value = data->sint; \
		            break; \
		        case DATA_TYPE_INT: \
		            value = data->intg; \
		            break; \
		        case DATA_TYPE_DINT: \
		            value = data->dint; \
		            break; \
		        case DATA_TYPE_USINT: \
		            value = data->usint; \
		            break; \
		        case DATA_TYPE_UINT: \
		            value = data->uint; \
		            break; \
		        case DATA_TYPE_UDINT: \
		            value = data->udint; \
		            break; \
		        case DATA_TYPE_REAL: \
		            value = data->real; \
		            break; \
		        case DATA_TYPE_LREAL: \
		            value = data->lreal; \
		            break; \
		        case DATA_TYPE_TIME: \
		            value = data->time; \
		            break; \
		        case DATA_TYPE_DATE: \
                    value = 0; \
                    break; \
                case DATA_TYPE_TOD: \
                    value = 0; \
                    break; \
                case DATA_TYPE_DT: \
                    value = 0; \
                    break; \
                case DATA_TYPE_STRING: \
                    value = 0; \
                    break; \
                case DATA_TYPE_WSTRING: \
                    value = 0; \
                    break; \
                case DATA_TYPE_POINTER: \
                    value = 0; \
                    break; \
                case DATA_TYPE_TABLE: \
                    value = 0; \
                    break; \
                case DATA_TYPE_USER: \
                    value = 0; \
                    break; \
		        default: \
		            break; \
		    }


#define SET_VALUE(data, value) \
        switch (data->type) { \
                case DATA_TYPE_BOOL: \
                    data->boolean = value->boolean; \
                    break; \
                case DATA_TYPE_SINT: \
                    data->sint = value->sint; \
                    break; \
                case DATA_TYPE_INT: \
                    data->intg = value->intg; \
                    break; \
                case DATA_TYPE_DINT: \
                    data->dint = value->dint; \
                    break; \
                case DATA_TYPE_USINT: \
                    data->usint = value->usint; \
                    break; \
                case DATA_TYPE_UINT: \
                    data->uint = value->uint; \
                    break; \
                case DATA_TYPE_UDINT: \
                    data->udint = value->udint; \
                    break; \
                case DATA_TYPE_REAL: \
                    data->real = value->real; \
                    break; \
                case DATA_TYPE_LREAL: \
                    data->lreal = value->lreal; \
                    break; \
                case DATA_TYPE_TIME: \
                    data->time = value->time; \
                    break; \
                case DATA_TYPE_DATE: \
				    data->date.date.day = value->date.date.day; \
				    data->date.date.month = value->date.date.month; \
				    data->date.date.year = value->date.date.year; \
                    break; \
                case DATA_TYPE_TOD: \
				    data->tod.tod.csec = value->tod.tod.csec; \
				    data->tod.tod.hour = value->tod.tod.hour; \
				    data->tod.tod.min = value->tod.tod.min; \
				    data->tod.tod.sec =  value->tod.tod.sec;\
                    break; \
                case DATA_TYPE_DT: \
                    ; \
                    break; \
                case DATA_TYPE_STRING: \
                    ; \
                    break; \
                case DATA_TYPE_WSTRING: \
                    ; \
                    break; \
                case DATA_TYPE_POINTER: \
                    ; \
                    break; \
                case DATA_TYPE_TABLE: \
                    ; \
                    break; \
                case DATA_TYPE_USER: \
                    ; \
                    break; \
                default: \
                    break; \
            }

void datalib_core_open(void);

#endif /* DATA_H_ */
