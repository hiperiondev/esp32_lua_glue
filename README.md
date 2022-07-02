
# ESP32 Lua Glue   [![Badge License]][License]

*A port of **Lua 4** for the **ESP32** / **ESP-IDF**.*

<br>

## Description

This project aims to recover the original <br>
use of Lua - that is - a glue language.

***Nothing more and nothing less.***

During these last years Lua has matured as a <br>
language becoming quite complete exceeding <br>
the original ideas for which it was created.

*It has also grown in both size and complexity which is* <br>
*not always desirable for small or speed-critical projects.*

**Lua 4** has several advantages for this:

- Static ( no more modifications )
- Easy to understand / modify
- Simple
- Small

If you really need a complete and mature language <br>
to embed in your applications you should consider <br>
alternatives like **[NodeMCU]**

<br>
<br>

## Libraries

Only basic libraries that can serve as an interface <br>
between the program and Lua's logic are added.

Any other functionality will be usage dependent <br>
and will need to be added based on your usage.

<br>
<br>

## Data Types

Minimal functionality for full external data types is <br>
provided, these types are specified in `IEC 61131-3`, <br>
please refer to the **[Wiki]** for more information.

<br>
<br>

## Networking

### WiFi

Can `connect`, `disconnect` and `scan`.

### TFTP

Provides a simple TFTP server.

<br>
<br>

## Memory

- Managed memory consumption

- Free space

- Tasks

<br>
<br>

## Todo

- Complete minimal libraries

- Add ssh to console

- Write documentation

- Add persistence / serialization 

<br>


<!----------------------------------------------------------------------------->

[Badge License]: https://img.shields.io/badge/License-GPL_3-blue.svg?style=for-the-badge

[NodeMCU]: https://nodemcu.readthedocs.io/en/release/
[Wiki]: https://github.com/hiperiondev/esp32_lua_glue/wiki

[License]: LICENSE
