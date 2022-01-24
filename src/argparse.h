#include<stdbool.h>
typedef struct{
    bool i;
    bool A;
    bool a;
    bool l;
    bool z;
    bool Y;
    bool one;
    bool R;
    char* file;
} Argz;

Argz parseArgz(int argc, char** argv);
