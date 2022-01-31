/**
 * @file dirtraversal.c
 * @author Skyler Calaman
 * @brief This file includes the definition for the dirForEach command. So far, that's all it has.
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "dirtraversal.h"
#include "utils.h"

#include <dirent.h>
#include <errno.h>

/**
 * @brief asdflkjh
 * 
 * @param dirName The name of the directory to be iterated through.
 * @param forEachFunc The "closure" that will be called on each dirent.
 * @return EaDirTraversalErrorType If any errors were encountered in the opening of the dir, the type of error encountered is returned here.
 */
EDirTraversalErrorType dirForEach(char *dirName, DirTraversalClosure forEachFunc) {
    DIR *dir;
    DirEnt *entry;

    dir = opendir(dirName);

    if (!dir) {
        switch (errno) {
            case EACCES:
                return DTET_ACCS_DEN;
            
            case ELOOP:
            case ENAMETOOLONG:
                return DTET_PATH_ERR;

            case ENOENT:
            case ENOTDIR:
                return DTET_INVAL_DIR;

            case EMFILE:
            case ENFILE:
                return DTET_FILE_ERR;

            default:
                panic("opendir failed with unknown error");
                
        }
    }

    while (1) {
        entry = readdir(dir);
        if (entry == NULL) break;
        CALL_CLOSURE(forEachFunc, entry);
    }

    if (closedir(dir) != 0) panic("closedir failed");

    return 0;
}
