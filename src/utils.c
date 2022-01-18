#include "utils.h"

/* TESTER CODE:
#include <stdio.h>


CREATE_CLOSURE_TYPE(int, int, Closure__int_int);

int x(int data, void *input) {
    printf("%s\t\tData: %d\n", (char *) input, data);
    return data - 1;
}


int main() {
    Closure__int_int cl = (Closure__int_int) {
        x,
        100
    };

    int z = CALL_CLOSURE(cl, (void *) "Hello!");

    printf("Return value: %d\n", z);

    return cl.closureData;
}
*/