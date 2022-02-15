#include "argparse.h"
#include "dirtraversal.h"
#include "utils.h"
#include "closures.h"
#include "inforetriever.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


void listFiles(Argz argz, struct winsize w, bool recursed) {
    /**
     * @brief Iterator variable.
     * 
     */
    int i;

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
     * @brief Contains the data for the closure that collects the file
     * info.
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
     * @brief The parsed arguments.
     * 
     */
    Argz passingArgz;

    // Counts the number of entries in the directory.
    entryCount = 0;
    dirForEach(argz.file, (DirTraversalClosure) { countEntries, &entryCount });

    // Creates an array that can contain the data for the number of
    // files in the directory.
    fileArr = malloc(entryCount * sizeof(FileInfo));

    // Creates a list that can have new file data appended to it.
    entryList = (EntryList) { 0, entryCount, fileArr, argz.file, argz.noPrintCharState };
    dirForEach(argz.file, (DirTraversalClosure) { addEntry, &entryList });

    // Sorts the data by name, could be expanded to be more general
    // later.
    qsort(fileArr, entryCount, sizeof(FileInfo), fileInfoComparer);

    // Initializes all of the lengths to 0.
    textSizes = (LenData) {0};

    // Creates the closure that will update the length data when
    // iterating through the directory entries.
    ldc = (LenDataClosure) {
        gatherLengths,
        &textSizes,
    };

    // Iterate through the directory entries.
    for (i = 0; i < entryCount; i++) CALL_CLOSURE(ldc, &fileArr[i]);

    // Get terminal size and put it in w.
    ioctl(0, TIOCGWINSZ, &w);

    // Initialize the printer data.
    printerData = (PrinterData) {
        w.ws_col,
        0,
        textSizes,
        argz
    };
    // Create the printer data closure.
    pdc = (PrinterClosure) {
        argz.one || argz.l
            ? linePrinter // Change this to linePrinter when you push.
            : basicPrinter,
        &printerData
    };

    if (recursed) printf("\n%s:\n", argz.file);

    // Iterate through the entries and print each of them 1 by 1.
    for (i = 0; i < entryCount; i++){
        if (filterByNameAndArgz(fileArr[i].name, argz)) {
            CALL_CLOSURE(pdc, &fileArr[i]);           
        }
    }
    if (pdc.closureData->currPos) printf("\n");
    
    
    if (argz.R) {
        for (i = 0; i < entryCount; i++) {
            char *name = fileArr[i].name;
            if (name[0] != '.' || !((name[1] == '\0') || (name[1] == '.' && name[2] == '\0'))) {
                if (filterByNameAndArgz(name, argz) && fileArr[i].fileType == FT_DIR) {
                    passingArgz = argz;
                    passingArgz.file = dsprintf(
                        "%s%s%s",
                        argz.file,
                        argz.file[strlen(argz.file) - 1] == '/'
                        ? ""
                        : "/",
                        name
                    );


                    listFiles(passingArgz, w, true);

                    free(passingArgz.file);
                }
            }
        }
    }

    for (i = 0; i < entryCount; i++) {
        free(fileArr[i].name);
        free(fileArr[i].cleanedName);
        free(fileArr[i].ownerName);
        free(fileArr[i].groupName);
    }

    free(fileArr);
}


int main(int argc, char **argv) {
    /**
     * @brief The parsed arguments.
     * 
     */
    Argz argz;

    /**
     * @brief Just a simple struct used for holding the width and height
     * of the terminal.
     * 
     */
    struct winsize w;

    // Parses the arguments
    argz = parseArgz(argc, argv); 

    // Get terminal size and put it in w.
    ioctl(0, TIOCGWINSZ, &w);

    listFiles(argz, w, false);

    return 0;
}
