#include "closures.h"
#include "utils.h"
#include "inforetriever.h"
#include "colors.h"

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

    entryList->entryArr[entryList->entryPointer++] = infoFromPath(entry->d_name, path, entryList->fileNameCleaningType);

    free(path);
}

//get lengths of output filename strings 
void gatherLengths(LenData *textSizes, void *file_vp) {
    FileInfo *file = (FileInfo *) file_vp;

    unsigned char inodeLen = numberLength(file->inodeNum);
    unsigned char fMetaLen = numberLength(file->fileOrMetaSize);
    unsigned char linkLen = numberLength(file->linkCount);
    
    size_t groupLen = strlen(file->groupName);
    size_t ownerLen = strlen(file->ownerName);
    size_t nameLen = strlen(file->cleanedName);

    size_t dateLen = 12; // TODO: MAKE SURE THIS IS CORRECT!
    

    IF_MORE_SET(textSizes->inodeLength,inodeLen);
    IF_MORE_SET(textSizes->fOrMetaSizeLength, fMetaLen);
    IF_MORE_SET(textSizes->linkLength, linkLen);

    IF_MORE_SET(textSizes->groupLength, groupLen);
    IF_MORE_SET(textSizes->ownerLength, ownerLen);
    IF_MORE_SET(textSizes->nameLength, nameLen);
    
    IF_MORE_SET(textSizes->dateLength, dateLen);
}

//TODO: check for -i and include inode, cehck for -z and nclude zzzz.z.zz.zzzz
void basicPrinter(PrinterData *printerData, void *file_vp) {
    
    FileInfo *file = (FileInfo *) file_vp;

    LenData *entryWidths = &printerData->entryWidths;

    int extraWidth;

    if(printerData->argz.i){
        extraWidth = calcPaddedWidth(entryWidths->nameLength + 1 + entryWidths->inodeLength); 
    }
    else{
        extraWidth = calcPaddedWidth(entryWidths->nameLength);
    }
    
    if (printerData->currPos + extraWidth >= printerData->width) {
        printf("\n");
        printerData->currPos = 0;
    }

    if(printerData->argz.z){
        int i;
        char printName[entryWidths->nameLength];
        for(i=0;i<entryWidths->nameLength;i++){
            switch(file->name[i]){
                case '.':
                    printName[i]='.';
                    break;
                case ' ':
                    printName[i]=' ';
                    break;
                case '-':
                    printName[i]='-';
                    break;
                case ':':
                    printName[i]=':';
                    break;
                case '/':
                    printName[i]='/';
                    break;
                default:
                    printName[i]='z';
                    break;
            }
        }
        printf("%s",*printName);
    }

    if(printerData->argz.i) printf("%*llu ", entryWidths->inodeLength, (unsigned long long) file->inodeNum);
    printf("%s%-*s%s\t", printerData->argz.Y ? getEntryColor(file) : fi, (int) entryWidths->nameLength, file->cleanedName, fi);
    
    

    printerData->currPos += extraWidth;
}

void linePrinter(PrinterData *printerData, void *file_vp){
    FileInfo *file=(FileInfo *)file_vp;
    if(printerData->argz.l){
        //in case its not obvious, i didnt get to this part yet. if you want to do the spacing rn,
        //feel free to. i'll try to figure out this part before its due lol :pain:

        printf("")

    }
    else{
        printf("%s\n",file->name);
    }

}
