#include "argparse.h"
#include "dirtraversal.h"
#include "utils.h"
#include "closures.h"
#include "inforetriever.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>

int fileInfoComparer(const void *a, const void *b) {
    return strcmp(((FileInfo *) a)->name, ((FileInfo *) b)->name);
}


bool filterByNameAndArgz(char *name, Argz argz) {
    if (name[0] == '.') {
        if (argz.a) return true;
        else if (argz.A) {
            if ((name[1] == '\0') || (name[1] == '.' && name[2] == '\0')) return false;
            else return true;
        } else return false;
    } else return true;
}


int main(int argc, char **argv) {
    int i;

    Argz argz;

    size_t entryCount;
    FileInfo *fileArr;
    EntryList entryList;
    LenData textSizes;
    PrinterData printerData;
    
    LenDataClosure ldc;
    PrinterClosure pdc;

    struct winsize w;


    argz = parseArgz(argc, argv);

    entryCount = 0;
    dirForEach(argz.file, (DirTraversalClosure) { countEntries, &entryCount });

    fileArr = malloc(entryCount * sizeof(FileInfo));

    entryList = (EntryList) { 0, entryCount, fileArr, argz.file };
    dirForEach(argz.file, (DirTraversalClosure) { addEntry, &entryList });


    qsort(fileArr, entryCount, sizeof(FileInfo), fileInfoComparer);


    textSizes = (LenData) {0};

    ldc = (LenDataClosure) {
        gatherLengths,
        &textSizes,
    };


    for (i = 0; i < entryCount; i++) CALL_CLOSURE(ldc, &fileArr[i]);

    ioctl(0, TIOCGWINSZ, &w);


    printerData = (PrinterData) {
        w.ws_col,
        0,
        textSizes
    };
    pdc = (PrinterClosure) {
        printer,
        &printerData
    };

    for (i = 0; i < entryCount; i++) if (filterByNameAndArgz(fileArr[i].name, argz)) CALL_CLOSURE(
        pdc,
        &fileArr[i]
    );
    printf("\n");

    return 0;
}
