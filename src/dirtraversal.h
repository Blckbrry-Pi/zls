#include "utils.h"

#ifndef ZLS_DIRTRAVERSE_H
#define ZLS_DIRTRAVERSE_H 1

typedef enum { DTET_ACCS_DEN, DTET_INVAL_DIR, DTET_PATH_ERR, DTET_FILE_ERR, DTET_NO_ERR } EDirTraversalErrorType;

CREATE_CLOSURE_TYPE(void, void *, DirTraversalClosure);



EDirTraversalErrorType dirForEach(char *dirName, DirTraversalClosure forEachFunc);

#endif