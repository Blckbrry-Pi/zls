#include "utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


char *dsprintf(char *fmt, ...) {
    size_t len;
    char *out;

    /* Declare a va_list type variable */
    va_list args1;
    va_list args2;

    /* Initialise the va_list variable with the ... after fmt */

    va_start(args1, fmt);
    va_copy(args2, args1);

    /* Forward the '...' to vprintf */
    len = vsnprintf(NULL, 0, fmt, args1);
    va_end(args1);

    out = malloc(sizeof(char) * (len + 1));


    vsprintf(out, fmt, args1);
    va_end(args2);

    return out;
}

void panic(const char *reason) {
    exit(1);
}


char *removeControlChars(char *input) {
    for (int i = 0; input[i] != '\0'; i++) if (iscntrl(input[i])) input[i] = '?';
    return input;
}
