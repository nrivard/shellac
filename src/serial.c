#include "serial.h"

void serial_put_string(const char *str) {
    while (*str) {
        serial_put(*str++);
    }
}
