#include "utils.h"
#include <string.h>
#include <ctype.h>

// return the string "trimmed"
char *trim(char *str) {
    char *end;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    end[1] = '\0';

    return str;
}

// removes all spaces in string
void remove_spaces(char *s) {
    char *d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

