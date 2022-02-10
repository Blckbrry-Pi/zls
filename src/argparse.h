#ifndef ZLS_ARGPARSE_H
#define ZLS_ARGPARSE_H

#include <stdbool.h>



typedef enum { NO_PRINT_b, NO_PRINT_B, NO_PRINT_w, NO_PRINT_q } ENoPrintCharArgz;

typedef struct{
    bool i;
    bool A;
    bool a;
    bool l;
    bool z;
    bool Y;
    bool one;
    ENoPrintCharArgz noPrintCharState;
    bool R;
    char* file;
} Argz;

Argz parseArgz(int argc, char** argv);


#endif
