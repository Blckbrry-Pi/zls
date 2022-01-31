#ifndef ZLS_CLOSURES_H
#define ZLS_CLOSURES_H

#include "utils.h"
#include "inforetriever.h"
#include <stdio.h>

void countEntries(void *count_vp, void *entry_vp);

typedef struct {
    size_t entryPointer;
    size_t entrtPointerMax;
    FileInfo *entryArr;

    char *dirname;
} EntryList;

void addEntry(void *entryList_vp, void *entry_vp);

typedef struct {
    unsigned char linkLength;
    size_t ownerLength;
    size_t groupLength;
    unsigned char fOrMetaSizeLength;
    size_t dateLength;
    size_t nameLength;
} LenData;

CREATE_CLOSURE_TYPE(void, LenData *, LenDataClosure);

void gatherLengths(LenData *textSizes, void *file_vp);

typedef struct {
    char **outArr;
    size_t position;
} GetStrData;

void getStrings(void *outArrData_vp, void *entry_vp);



typedef struct {
    size_t width;
    size_t currPos;
    LenData entryWidths;
} PrinterData;

CREATE_CLOSURE_TYPE(void, PrinterData *, PrinterClosure);

void printer(PrinterData *printerData, void *entry_vp);

#endif
