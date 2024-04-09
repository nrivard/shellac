#include "string.h"
#include <stdio.h>

int strcmp(const char *str1, const char *str2) {
    register const char *left = str1, *right = str2;
    register char result;
    for (;;) {
        if (!*left) {
            return *right ? -1 : 0;
        } else if (!*right) {
            return 1;
        } else if ((result = *left++ - *right++) != 0) {
            return (int)result;
        }
    }
}
