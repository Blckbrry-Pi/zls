#include <sys/stat.h>

#include "inforetriever.h"
#include "utils.h"

#define GET_PERM_NUMBER(num, readPerm, writePerm, execPerm) (((num && readPerm) << 2) + ((num && writePerm) << 1) + ((num && execPerm) << 0))

FileInfo infoFromPath(char *name, char *path) {
    struct stat infoStatFormat;

    FileInfo infoOutput;

    stat(path, &infoStatFormat);

    infoOutput.fileOrMetaSize = infoStatFormat.st_size;
    

    switch ((infoStatFormat.st_mode) & S_IFMT) {
        case S_IFBLK:
            infoOutput.fileType = FT_BLCK;
            break;

        case S_IFCHR:
            infoOutput.fileType = FT_CHAR;
            break;

        case S_IFIFO:
            infoOutput.fileType = FT_FIFO;
            break;

        case S_IFREG:
            infoOutput.fileType = FT_REG;
            break;

        case S_IFDIR:
            infoOutput.fileType = FT_DIR;
            break;

        case S_IFLNK:
            infoOutput.fileType = FT_LINK;
            break;

        case S_IFSOCK:
            infoOutput.fileType = FT_SOCK;
    }

    infoOutput.groupName = "TODO: MAKE IT ACTUALLY GET THE GROUP NAME...";
    infoOutput.ownerName = "TODO: MAKE IT ACTUALLY GET THE OWNER NAME...";

    #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
    infoOutput.lastModified = infoStatFormat.st_mtimespec.tv_sec;
    #else
    infoOutput.lastModified = infoStatFormat.st_mtime;
    #endif

    infoOutput.linkCount = infoStatFormat.st_nlink;

    infoOutput.name = dsprintf("%s", name);

    infoOutput.perms = (Perms) {
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR),
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXG, S_IRGRP, S_IWGRP, S_IXGRP),
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH),
    };
    
    infoOutput.inodeNum = infoStatFormat.st_ino;

    return infoOutput;
}
