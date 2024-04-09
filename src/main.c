#include "shellac.h"
#include <stdio.h>

static char SampleData[0x80] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
};

char stub_getc() {
    return getchar();
}

void stub_putc(char byte) {
    putchar(byte);
}

int main() {
    ShellacConfig config = {
        stub_getc,
        stub_putc
    };

    printf("Sample data located at: %p\n", &SampleData);

    shellac_main(&config);
}
