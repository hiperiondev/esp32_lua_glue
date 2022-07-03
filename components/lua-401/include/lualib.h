/*
 ** $Id: lualib.h,v 1.14 2000/10/27 16:15:53 roberto Exp $
 ** Lua standard libraries
 ** See Copyright Notice in lua.h
 */

#ifndef lualib_h
#define lualib_h

#include "lua.h"

#ifndef LUALIB_API
#define LUALIB_API  extern
#endif

#define LUA_ALERT  "_ALERT"

LUALIB_API void lua_baselibopen(lua_State *L);
LUALIB_API void lua_iolibopen(lua_State *L);
LUALIB_API void lua_strlibopen(lua_State *L);
LUALIB_API void lua_mathlibopen(lua_State *L);
LUALIB_API void lua_dblibopen(lua_State *L);
LUALIB_API void lua_memorylibopen(lua_State *L);
LUALIB_API void lua_networklibopen(lua_State *L);
LUALIB_API void lua_datalib_coreopen(lua_State *L);
LUALIB_API void lua_datalib_arithmeticopen(lua_State *L);
LUALIB_API void lua_datalib_bit_shiftopen(lua_State *L);
LUALIB_API void lua_datalib_bitwise_booleanopen(lua_State *L);
LUALIB_API void lua_datalib_comparisonopen(lua_State *L);
LUALIB_API void lua_datalib_conversionopen(lua_State *L);
LUALIB_API void lua_datalib_date_timeopen(lua_State *L);
LUALIB_API void lua_datalib_mathematicalopen(lua_State *L);
LUALIB_API void lua_datalib_stringopen(lua_State *L);
LUALIB_API void lua_datalib_systemopen(lua_State *L);
LUALIB_API void lua_datalib_validationopen(lua_State *L);

/* Auxiliary functions (private) */

const char *luaI_classend(lua_State *L, const char *p);
       int luaI_singlematch(int c, const char *p, const char *ep);

#endif
