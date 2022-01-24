

#ifndef NULL
#define NULL 0
#endif


#ifndef ZLS_UTILS_H
#define ZLS_UTILS_H


#define CALL_CLOSURE(closure, input) (*closure.func)(closure.closureData, input)

#define CREATE_CLOSURE_TYPE(returnType, dataType, structName) typedef struct { \
    returnType (*func)(dataType, void *); \
    dataType closureData; \
} structName


#include <dirent.h>
typedef struct dirent DirEnt;


#define BACKTRACE_MAX 1000


typedef struct {
    void **returnAddresses;
    char *message;
} Backtrace;


#include <stdbool.h>

#define DECLARE_RESULT_TYPE(OkType) typedef struct {  \
    bool isOk;                   \
    Backtrace err;               \
    OkType ok;                   \
} Result__ ## OkType ## __

#define RESULT(OkType)  Result__ ## OkType ## __

#define OK(okVal) { \
    true,           \
    (Backtrace) {   \
        NULL,       \
        NULL        \
    },              \
    okVal           \
}

#define ERR(backtrace, errMsg) { \
    false,                       \
    (Backtrace) {                \
        backtrace,               \
        errMsg                   \
    }                            \
}

#define _OK 1
#define __OK(result) result.isOk
#define __GET_OK(result) result.ok
#define _ERR 1
#define __ERR(result) !result.isOk
#define __GET_ERR(result) result.err

#define RESULT_AS(binding, result, match) \
if ((_ ## match) &&  (__ ## match (result))) \
    for (int RES_OK_AS__TEMP_VAR_1 = 0; RES_OK_AS__TEMP_VAR_1 == 0; RES_OK_AS__TEMP_VAR_1++) \
        for (binding = __GET_ ## match (result); RES_OK_AS__TEMP_VAR_1 == 0; RES_OK_AS__TEMP_VAR_1++)



char *dsprintf(char *fmt, ...);

void panic(const char *reason);

#endif
