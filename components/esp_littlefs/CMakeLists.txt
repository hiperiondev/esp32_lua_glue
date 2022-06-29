file(
    GLOB_RECURSE
        SOURCES
            src/*.c
            src/littlefs/*.c
            src/littlefs/bd/*.c
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS
        include
        src/littlefs
        src/littlefs/bd
    REQUIRES
        lua-401
        lua-401_port
        sdmmc
)
