#include "closures.h"
#include "utils.h"
#include "inforetriever.h"

#include <dirent.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define IF_MORE_SET(lvalue, comparisonNumber) if (comparisonNumber > lvalue) lvalue = comparisonNumber

void countEntries(void *count_vp, void *entry_vp) {
    size_t *count = (size_t *) count_vp;
    (*count)++;
}

void addEntry(void *entryList_vp, void *entry_vp) {
    EntryList *entryList = (EntryList *) entryList_vp;
    DirEnt *entry = (DirEnt *) entry_vp;
    
    if (entryList->entryPointer >= entryList->entrtPointerMax) return;

    char *path = dsprintf(
        "%s%s%s",
        entryList->dirname,
        entryList->dirname[strlen(entryList->dirname) - 1] == '/'
          ? ""
          : "/",
        entry->d_name
    );

    entryList->entryArr[entryList->entryPointer++] = infoFromPath(entry->d_name, path);

    free(path);
}

void gatherLengths(LenData *textSizes, void *file_vp) {
    FileInfo *file = (FileInfo *) file_vp;

    unsigned char fMetaLen = numberLength(file->fileOrMetaSize);
    unsigned char linkLen = numberLength(file->linkCount);
    
    size_t groupLen = strlen(file->groupName);
    size_t ownerLen = strlen(file->ownerName);
    size_t nameLen = strlen(file->name);

    size_t dateLen = 12; // TODO: MAKE SURE THIS IS CORRECT!
    

    IF_MORE_SET(textSizes->fOrMetaSizeLength, fMetaLen);
    IF_MORE_SET(textSizes->linkLength, linkLen);

    IF_MORE_SET(textSizes->groupLength, groupLen);
    IF_MORE_SET(textSizes->ownerLength, ownerLen);
    IF_MORE_SET(textSizes->nameLength, nameLen);
    
    IF_MORE_SET(textSizes->dateLength, dateLen);
}

void getStrings(void *outArrData_vp, void *entry_vp) {
    GetStrData *outArrData = (GetStrData *) outArrData_vp;
    DirEnt *entry = (DirEnt *) entry_vp;

    strcpy(outArrData->outArr[outArrData->position++], entry->d_name);
}

void printer(PrinterData *printerData, void *file_vp) {
    FileInfo *file = (FileInfo *) file_vp;

    int extraWidth = 8 - printerData->entryWidths.nameLength % 8 + printerData->entryWidths.nameLength;

    if (printerData->currPos + extraWidth >= printerData->width) {
        printf("\n");
        printerData->currPos = 0;
    }
    printf("%-*s\t", (int) printerData->entryWidths.nameLength, file->name);
    printerData->currPos += extraWidth;
}
