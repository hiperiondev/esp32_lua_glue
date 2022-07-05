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

#ifndef LUA401_PORT_H_
#define LUA401_PORT_H_

#define MOUNT_POINT           "/littlefs"
#define PARTITION_LABEL       "littlefs"

#include <stdio.h>
#include <stdlib.h>

#define F_OPEN(FN, OT)        popen(FN, OT)
#define F_REOPEN(FN, OT, ST)  freopen(FN, OT, ST)
#define F_REMOVE(FN)          remove(FN)
#define F_RENAME(ON, NN)      rename(ON, NN)


#endif /* LUA25_PORT_H_ */
