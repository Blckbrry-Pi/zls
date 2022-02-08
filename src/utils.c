#include "utils.h"
#include "string.h"

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


    vsprintf(out, fmt, args2);
    va_end(args2);

    return out;
}

unsigned char numberLength(size_t number) {
    unsigned char count = 0;
    size_t currentNum = number;

    do {
        count++;
    } while (currentNum /= 10);

    return count;
}

void panic(const char *reason) {
    printf("Panic called! Reason: %s\n", reason);
    exit(1);
}


char *removeControlChars(char *input, ENoPrintCharArgz cleanType) {
    char *outStr;
    size_t i;
    size_t j;
    size_t len;
    switch (cleanType) {
        case NO_PRINT_q: 
            outStr = malloc(sizeof(char) * (strlen(input) + 1));
            strcpy(outStr, input);
            for (i = 0; outStr[i] != '\0'; i++) if (iscntrl(outStr[i])) outStr[i] = '?';
            break;

        case NO_PRINT_w:
            outStr = dsprintf("%s", input);
            break;

        case NO_PRINT_b:
            panic(dsprintf("Unimplemented [TODO]! (Line: %zd, File: %s)", __LINE__, __FILE__)); // TODO: get this working.

        
        case NO_PRINT_B:
            for (i = 0; input[i] != '\0'; i++) {
                len++;
                if (iscntrl(input[i])) len += 3; 
            }
            outStr = malloc(sizeof(char) * (len + 1));
            for (i = 0, j = 0; input[i] != '\0'; i++) {
                if (iscntrl(input[i])) {
                    sprintf(outStr + j, "\\%03o", input[i]);
                    j += 4;
                } else {
                    outStr[j] = input[i];
                    j += 1;
                }
            }
            outStr[j] = '\0';
            break;
    }
    return outStr;
}

size_t calcPaddedWidth(size_t unpaddedWidth) {
    return 8 - unpaddedWidth % 8 + unpaddedWidth;
}
