#include "args.h"
#include "dirtraversal.h"
#include "utils.h"

#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <strings.h>

void gatherLengths(void *maxLen_vp, void *entry_vp) {
    size_t *maxLen = (size_t *) maxLen_vp;
    DirEnt *entry = (DirEnt *) entry_vp;

    size_t entryStrLen = strlen(entry->d_name);
    if (entryStrLen > *maxLen) *maxLen = entryStrLen;
}

typedef struct {
    size_t width;
    size_t currPos;
    size_t entryWidth;
} PrinterData;

void printer(void *printerData_vp, void *entry_vp) {
    PrinterData *printerData = (PrinterData *) printerData_vp;
    DirEnt *entry = (DirEnt *) entry_vp;

    if (printerData->currPos + printerData->entryWidth + 8 >= printerData->width) printf("\n");
    printf("%-*s\t", (int) printerData->entryWidth, entry->d_name);
}

int main(int argc, char **argv) {
    size_t maxLen = 0;
    struct winsize w;

    dirForEach(".", (DirTraversalClosure) { gatherLengths, &maxLen });

    ioctl(0, TIOCGWINSZ, &w);

    dirForEach(".", (DirTraversalClosure) { printer, &(PrinterData) { w.ws_col, 0, maxLen } });
    printf("\n");
}
