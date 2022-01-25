/**
 * @file dirtraversal.h
 * @author Skyler Calaman
 * @brief The header file declaring the main directory-walking function.
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "utils.h"

#ifndef ZLS_DIRTRAVERSE_H
#define ZLS_DIRTRAVERSE_H

typedef enum { DTET_ACCS_DEN, DTET_INVAL_DIR, DTET_PATH_ERR, DTET_FILE_ERR, DTET_NO_ERR } EDirTraversalErrorType;

CREATE_CLOSURE_TYPE(void, void *, DirTraversalClosure);



EDirTraversalErrorType dirForEach(char *dirName, DirTraversalClosure forEachFunc);

#endif
