#pragma once

extern char serial_get(void);
extern void serial_put(char);

void serial_put_string(const char *);
