#include "argparse.h"
#include "dirtraversal.h"
#include "utils.h"
#include "closures.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/ioctl.h>

int stringComparer(const void *a, const void *b) {
    return strcmp(*(const char **) a, *(const char **) b);
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
    Argz argz;

    LenCountData textSizes;
    
    struct winsize w;
    PrinterData pd;
    PrinterClosure pc;

    argz = parseArgz(argc, argv);

    textSizes = (LenCountData) { 0, 0 };
    dirForEach(".", (DirTraversalClosure) { gatherLengthAndCount, &textSizes });

    char **fileNameArr = malloc(textSizes.count * sizeof(char *));
    for (size_t i = 0; i < textSizes.count; i++) fileNameArr[i] = malloc((textSizes.length + 1) * sizeof(char));
    dirForEach(".", (DirTraversalClosure) { getStrings, &(GetStrData) {fileNameArr, 0} });

    qsort(fileNameArr, textSizes.count, sizeof(char *), stringComparer);

    ioctl(0, TIOCGWINSZ, &w);
    pd = (PrinterData) { w.ws_col, 0, textSizes.length };
    pc = (PrinterClosure) { printer, &pd };

    for (int i = 0; i < textSizes.count; i++) if (filterByNameAndArgz(fileNameArr[i], argz)) CALL_CLOSURE(pc, fileNameArr[i]);
    printf("\n");

    return 0;
}
