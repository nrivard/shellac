#pragma once

typedef struct {
    char (*getc)(void);
    void (*putc)(char);
} ShellacConfig;

void shellac_main(ShellacConfig *config);
