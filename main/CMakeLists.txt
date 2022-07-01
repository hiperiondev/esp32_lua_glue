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
        esp_littlefs
        lua-401
        lua-401_libraries
        lua-401_data_libraries
        lua-401_port
        sshd
)