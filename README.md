# Port of Lua 4 for ESP32 (ESP-IDF)

This project aims to recover the original use of Lua, that is, a glue language. Nothing more and nothing less.

During these last years LUA has matured as a language becoming really complete exceeding the original ideas for which it was created.

It has also grown in both size and complexity which is not always desirable for small or speed-critical projects.

LUA 4 has several advantages for this: it is small, it is static (no more modifications), it is simple, it is easy to understand and modify.

If you really need a complete and mature language to embed in your applications you should consider alternatives like [NODEMCU](https://nodemcu.readthedocs.io/en/release/)

# LIBRARIES

Only basic libraries that can serve as an interface between the application and the logic in LUA are added. Any other functionality will be usage dependent and will need to be added based on your usage.

## DATA TYPES
Minimal functionality for full external data types is added. These types are those specified in IEC 61131-3.<p>
Please read the [Wiki](https://github.com/hiperiondev/esp32_lua_glue/wiki).

## NETWORKING
- Wi-Fi connection, disconnection and scan
- A simple TFTP server

## MEMORY
- Consumption control, free space and tasks

#
### TODO
- Complete minimal libraries
- Create documentation
- Add persistence/serialization 
