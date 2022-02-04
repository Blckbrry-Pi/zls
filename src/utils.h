

#ifndef NULL
#define NULL 0
#endif


#ifndef ZLS_UTILS_H
#define ZLS_UTILS_H

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

/**
 * @brief Calls a closure struct.
 * 
 */
#define CALL_CLOSURE(closure, input) (*closure.func)(closure.closureData, input)

/**
 * @brief Creates a new type of closure.
 * 
 */
#define CREATE_CLOSURE_TYPE(returnType, dataType, structName) typedef struct { \
    returnType (*func)(dataType, void *); \
    dataType closureData; \
} structName


typedef struct dirent DirEnt;

// UNUSED
/*
#define BACKTRACE_MAX 1000



typedef struct {
    void **returnAddresses;
    char *message;
} Backtrace;



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
*/

/**
 * @brief Similar to sprintf, except it allocates the buffer for itself.
 * 
 */
char *dsprintf(char *fmt, ...);

/**
 * @brief Takes a number and returns the number of characters in it (to
 * allow for alignment of lengths between different numbers.
 * 
 * @param number The number to get the number of digits from.
 * @return The number of digits in the character.
 */
unsigned char numberLength(size_t number);

/**
 * @brief Replaces control characters in place (and also returns) in a
 * string. 
 * 
 * @param input The string to replace the characters in.
 * @return The same string passed in, with the control characters
 * replaced.
 */
char *removeControlChars(char *input);

/**
 * @brief Call this function when you want to exit the program because
 * of an error that is not recoverable and can't be passed higher on the
 * call stack.
 * 
 * @param reason 
 */
void panic(const char *reason);

size_t calcPaddedWidth(size_t unpaddedWidth);

#endif
