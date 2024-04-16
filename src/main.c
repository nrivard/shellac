#include "shellac.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>

static char SampleData[0x80] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
    1, 2, 3, 4, 5, 6, 7, 8,
};

char serial_get() {
    return getchar();
}

void serial_put(char byte) {
    putchar(byte);
}

int main() {
    printf("Sample data located at: %p\n", &SampleData);

    shellac_main();
}
