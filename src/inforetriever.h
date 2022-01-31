#ifndef ZLS_INFORETRIEVER_H
#define ZLS_INFORETRIEVER_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef enum {
    FT_REG = '-',
    FT_DIR = 'd',
    FT_LINK = 'l',
    FT_FIFO = 'p',
    FT_SOCK = 's',
    FT_CHAR = 'c',
    FT_BLCK = 'b',
    FT_DOOR = 'D',
} EFileType;

typedef struct {
    char ownerPerms;
    char groupPerms;
    char otherPerms;
    bool hasExAttr;
} Perms;

typedef struct {
    EFileType fileType;
    Perms perms;
    size_t linkCount;
    char *ownerName;
    char *groupName;
    size_t fileOrMetaSize;
    time_t lastModified;
    char *name;
} FileInfo;

FileInfo infoFromPath(char *name, char *path);

#endif
