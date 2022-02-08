#ifndef ZLS_CLOSURES_H
#define ZLS_CLOSURES_H

#include "argparse.h"
#include "utils.h"
#include "inforetriever.h"
#include <stdio.h>

void countEntries(void *count_vp, void *entry_vp);

typedef struct {
    size_t entryPointer;
    size_t entrtPointerMax;
    FileInfo *entryArr;

    char *dirname;
    ENoPrintCharArgz fileNameCleaningType;
} EntryList;

void addEntry(void *entryList_vp, void *entry_vp);

typedef struct {
    unsigned char linkLength;
    size_t ownerLength;
    size_t groupLength;
    unsigned char fOrMetaSizeLength;
    size_t dateLength;
    size_t nameLength;
    unsigned char inodeLength;
} LenData;

CREATE_CLOSURE_TYPE(void, LenData *, LenDataClosure);

void gatherLengths(LenData *textSizes, void *file_vp);




typedef struct {
    size_t width;
    size_t currPos;
    LenData entryWidths;
    Argz argz;
} PrinterData;

CREATE_CLOSURE_TYPE(void, PrinterData *, PrinterClosure);

void basicPrinter(PrinterData *printerData, void *entry_vp);



#endif
