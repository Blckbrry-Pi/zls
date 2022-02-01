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

/**
 * @brief This struct holds the permissions data for a single directory
 * entry. It holds owner, group, and other permissions, and indicates
 * whether or not the entry has extended attributes.
 * 
 */
typedef struct {
    char ownerPerms; // Octal number representing owner permissions.
    char groupPerms; // Octal number representing group permissions.
    char otherPerms; // Octal number representing everyone else's permissions
    bool hasExAttr;  // Unimplemented, but should hold whether the file has extended attributes.
} Perms;

/**
 * @brief This struct holds the info gathered from stat that is relevant
 * to the -l flag.
 * 
 */
typedef struct {
    EFileType fileType;    // The type of the directory entry.
    Perms perms;           // The perm struct representing what the perms are for the entry.
    size_t linkCount;      // I'm not really sure what this means, but it's what stat reports as the hard link count.
    char *ownerName;       // Name of the owner.
    char *groupName;       // Name of the group.
    size_t fileOrMetaSize; // File size, metadata size, link size, or other, depending on the entry type.
    time_t lastModified;   // Time of last modification.
    char *name;            // The name of the entry.
} FileInfo;

/**
 * @brief This takes the name of a entry in a directory and it's path,
 * and returns a FileInfo struct, which contains that entry's info.
 * 
 * @param name The name of the entry without the path leading up to it.
 * @param path The path to the entry.
 * @return A FileInfo struct containing information about that entry. 
 */
FileInfo infoFromPath(char *name, char *path);

#endif
