#include "../utils.h"

#include <stdio.h>
#include <stdlib.h>


DECLARE_RESULT_TYPE(char);

RESULT(char) z() {
    RESULT(char) x;
    
    if (/* some integer*/ true) x = (RESULT(char)) OK('b');
    else {
        void *vp = NULL;
        x = (RESULT(char)) ERR(&vp, "aaaaaaaaaaaaaaaaa");
    }
    
    RESULT_AS(char c, x, OK) {
        char *out = dsprintf("Result is OK! Contained character is '%c'.\n", c);
        printf("%s", out);
        free(out);
    }
    RESULT_AS(Backtrace b, x, ERR) {
        char *out = dsprintf("Result is ERR! Error message is '%s'.\n", b.message);
        printf("%s", out);
        free(out);
    }

    return (RESULT(char)) OK('g');
}


int main() {
    z();

    return 0;
}
