#ifndef ZLS_UTILS_H
#define ZLS_UTILS_H


#define CALL_CLOSURE(closure, input) (*closure.func)(closure.closureData, input)

#define CREATE_CLOSURE_TYPE(returnType, dataType, structName) typedef struct { \
    returnType (*func)(dataType, void *); \
    dataType closureData; \
} structName;

#include <dirent.h>
typedef struct dirent DirEnt;



#endif


#ifndef NULL
#define NULL 0
#endif
