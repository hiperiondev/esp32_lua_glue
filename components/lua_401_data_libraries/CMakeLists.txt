file(
    GLOB_RECURSE
        SOURCES
            ./*.c
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS
        .
    REQUIRES
        lua-401
        lua-401_port
        nvs_flash
        tracklloc
        sshd
)
