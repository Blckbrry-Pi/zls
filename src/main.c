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
    /**
     * @brief Iterator variable.
     * 
     */
    int i;

    /**
     * @brief The parsed arguments.
     * 
     */
    Argz argz;

    /**
     * @brief Holds the number of entries in the directory.
     * 
     */
    size_t entryCount;
    /**
     * @brief The actual array of entry data.
     * 
     */
    FileInfo *fileArr;
    /**
     * @brief Contains the data for the closure that collects the file info.
     * 
     */
    EntryList entryList;
    /**
     * @brief Holds the relevant length data.
     * 
     */
    LenData textSizes;
    /**
     * @brief Holds the data for the printing closure.
     * 
     */
    PrinterData printerData;
    
    /**
     * @brief Holds the closure that calculates the maximum length of
     * different attributes of the entries.
     * 
     */
    LenDataClosure ldc;
    /**
     * @brief Holds the closure that prints the data out.
     * 
     */
    PrinterClosure pdc;

    /**
     * @brief Just a simple struct used for holding the width and height
     * of the terminal.
     * 
     */
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
