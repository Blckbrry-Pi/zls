#include "dirtraversal.h"
#include "utils.h"

#include <dirent.h>
#include <errno.h>


EDirTraversalErrorType dirForEach(char *dirName, DirTraversalClosure forEachFunc) {

    DIR *dir;
    DirEnt *entry;

    dir = opendir(".");

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
        }
    }

    while (1) {
        entry = readdir(dir);
        if (entry == NULL) break;
        CALL_CLOSURE(forEachFunc, entry);
    }

    closedir(dir);

    return 0;
}