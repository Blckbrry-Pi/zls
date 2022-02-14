#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "inforetriever.h"
#include "utils.h"

#define GET_PERM_NUMBER(num, readPerm, writePerm, execPerm) (((num & readPerm) ? (1 << 2) : 0) + ((num & writePerm) ? (1 << 1) : 0) + ((num & execPerm) ? (1 << 0) : 0))

FileInfo infoFromPath(char *name, char *path, ENoPrintCharArgz fileNameCleaningType) {
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

    infoOutput.ownerName = getpwuid(infoStatFormat.st_uid)->pw_name;
    infoOutput.groupName = getgrgid(infoStatFormat.st_gid)->gr_name;
    if(infoOutput.ownerName==NULL){
       infoOutput.ownerName = "NULL"; 
    }
    if(infoOutput.groupName==NULL){
        infoOutput.groupName="NULL";
    }   


   // infoOutput.ownerName = getpwuid(infoStatFormat.st_uid)->pw_name;    
    //infoOutput.groupName = getgrgid(infoStatFormat.st_gid)->gr_name;   

    #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
    infoOutput.lastModified = infoStatFormat.st_mtimespec.tv_sec;
    #else
    infoOutput.lastModified = infoStatFormat.st_mtime;
    #endif

    infoOutput.linkCount = infoStatFormat.st_nlink;

    infoOutput.name = dsprintf("%s", name);

    infoOutput.cleanedName = removeControlChars(infoOutput.name, fileNameCleaningType);

    infoOutput.perms = (Perms) {
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR),
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXG, S_IRGRP, S_IWGRP, S_IXGRP),
        GET_PERM_NUMBER(infoStatFormat.st_mode & S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH),
    };
    
    infoOutput.inodeNum = infoStatFormat.st_ino;

    return infoOutput;
}
