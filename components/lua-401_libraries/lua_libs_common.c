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
#include "luadebug.h"
#include "lualib.h"
#include "lua-401_port.h"

void strupp(char *beg) {
    while ((*beg++ = toupper(*beg)))
        ;
}

static void lua_printstack(FILE *f) {
    char fn_bogus[]="(bogus filename)";
    int level = 0;
    lua_Object func;
    fprintf(f, "Active Stack:\n");
    while ((func = lua_stackedfunction(level++)) != LUA_NOOBJECT) {
        char *name;
        int currentline;
        fprintf(f, "\t");
        switch (*lua_getobjname(func, &name)) {
            case 'g':
                fprintf(f, "function %s", name);
                break;
            case 'f':
                fprintf(f, "`%s' fallback", name);
                break;
            default: {
                char *filename;
                int linedefined;
                lua_funcinfo(func, &filename, &linedefined);
                if(filename == NULL)
                    filename = fn_bogus;
                if (linedefined == 0)
                    fprintf(f, "main of %s", filename);
                else if (linedefined < 0)
                    fprintf(f, "%s", filename);
                else fprintf(f, "function (%s:%d)", filename, linedefined);
            }
        }
        if ((currentline = lua_currentline(func)) > 0)
            fprintf(f, " at line %d", currentline);
        fprintf(f, "\n");
    }
}

void errorfb(void) {
    char *s = lua_opt_string(1, "(no messsage)", NULL);
    PRINTF("lua: %s\n", s);
    lua_printstack(stdout);
}
