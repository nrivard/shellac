#pragma once

extern char serial_get(void);
extern void serial_put(char);

void serial_put_string(const char *);
void serial_put_char(const char c);
void serial_put_long(const unsigned long d);