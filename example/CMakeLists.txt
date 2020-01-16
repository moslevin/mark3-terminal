project(terminal_ex)

set(BIN_SOURCES
    cmd.cpp
    cmd_args.cpp
    cmd_cd.cpp
    cmd_dumpstack.cpp
    cmd_ls.cpp
    cmd_pwd.cpp
    cmd_readmem.cpp
    cmd_testpattern.cpp
    cmd_threads.cpp
    cmd_unknown.cpp
    cmd_uptime.cpp
    file_props.cpp
    kernel_safe_guard.cpp
    main.cpp
    node_dev.cpp
    node_dir.cpp
    service.cpp
    shell_env.cpp
)

mark3_add_executable(terminal_ex ${BIN_SOURCES})

target_link_libraries(terminal_ex.elf
    mark3
    logger
    memutil
    terminal
    uartplus
    libc
)
