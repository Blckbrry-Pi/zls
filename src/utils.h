#ifndef ZLS_UTILS_H
#define ZLS_UTILS_H 1


#define CALL_CLOSURE(closure, input) (*closure.func)(closure.closureData, input)

#define CREATE_CLOSURE_TYPE(returnType, dataType, structName) typedef struct { \
    returnType (*func)(dataType, void *); \
    dataType closureData; \
} structName;

#include <dirent.h>
typedef struct dirent DirEnt;


// typedef struct {
    
// } TraceStruct;

// #define TRACE(funcName, ...) 

#endif


#ifndef NULL
#define NULL 0
#endif
