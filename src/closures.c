#include "closures.h"
#include "utils.h"

#include <dirent.h>
#include <stdio.h>
#include <strings.h>

void gatherLengthAndCount(void *textSizes_vp, void *entry_vp) {
    LenCountData *textSizes = (LenCountData *) textSizes_vp;
    DirEnt *entry = (DirEnt *) entry_vp;

    size_t entryStrLen = strlen(entry->d_name);
    
    if (entryStrLen > textSizes->length) textSizes->length = entryStrLen;
    textSizes->count++;
}

void getStrings(void *outArrData_vp, void *entry_vp) {
    GetStrData *outArrData = (GetStrData *) outArrData_vp;
    DirEnt *entry = (DirEnt *) entry_vp;

    strcpy(outArrData->outArr[outArrData->position++], entry->d_name);
}

void printer(PrinterData *printerData, void *filename) {
    if (printerData->currPos + printerData->entryWidth + 8 >= printerData->width) {
        printf("\n");
        printerData->currPos = 0;
    }
    printf("%-*s\t", (int) printerData->entryWidth, (char *) filename);
    printerData->currPos += 8 - printerData->entryWidth % 8 + printerData->entryWidth;
}
