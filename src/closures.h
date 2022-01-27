#include "utils.h"
#include <stdio.h>

typedef struct {
    size_t length;
    size_t count;
} LenCountData;

void gatherLengthAndCount(void *textSizes_vp, void *entry_vp);

typedef struct {
    char **outArr;
    size_t position;
} GetStrData;

void getStrings(void *outArrData_vp, void *entry_vp);

typedef struct {
    size_t width;
    size_t currPos;
    size_t entryWidth;
} PrinterData;

CREATE_CLOSURE_TYPE(void, PrinterData *, PrinterClosure);

void printer(PrinterData *printerData, void *entry_vp);
