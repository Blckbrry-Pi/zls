#include "closures.h"
#include "utils.h"
#include "inforetriever.h"
#include "colors.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void permtos3(int perm, char* s){

        s[0]=perm & 04 ? 'r' : '-';
        s[1]=perm & 02 ? 'w' : '-';
        s[2]=perm & 01 ? 'x' : '-';

}

char enumtochar(EFileType fileType){
    char c;
    switch(fileType){
        case(FT_REG):
            c='-';
            break;
        case(FT_DIR):
            c='d';
            break;
        case(FT_LINK):
            c='l';
            break;
        case(FT_FIFO):
            c='p';
            break;
        case(FT_SOCK):
            c='s';
            break;
        case(FT_CHAR):
            c='c';
            break;
        case(FT_BLCK):
            c='b';
            break;
        case(FT_DOOR):
            c='D';
            break;
        default:
            c='?';
            break;
    }
    return c;
}

void timestampToTime(time_t timestamp,struct tm* timeInfo){
    timeInfo=localtime(&timestamp);
    
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
        //char printName[entryWidths->nameLength];
        //printName[(entryWidths->nameLength)-1]='\0';
        //printf("entryWidths->nameLength: %lu, file->cleanedName.length: %lu\n",entryWidths->nameLength,strlen(file->cleanedName));
        for(i=0;i<strlen(file->cleanedName);i++){
            switch(file->cleanedName[i]){
                case '\t':
                case '.':
                case ' ':
                case '-':
                case ':':
                case '/':
                    break;
                default:
                    file->cleanedName[i]='z';
                    break;
            }
        }
        //printf("original: %s\n formatted: %s\n",file->cleanedName, printName);
    }

    if(printerData->argz.i) printf("%*llu ", entryWidths->inodeLength, (unsigned long long) file->inodeNum);
    printf("%s%-*s%s\t", printerData->argz.Y ? getEntryColor(file) : fi, (int) entryWidths->nameLength, file->cleanedName, fi);
    
    

    printerData->currPos += extraWidth;
}

void linePrinter(PrinterData *printerData, void *file_vp){
    FileInfo *file=(FileInfo *)file_vp;
    if(printerData->argz.l){
        char permstr[11];
        permstr[9]='\0';
        permstr[0]=enumtochar(file->fileType);
        permtos3(file->perms.ownerPerms,&permstr[1]);
        permtos3(file->perms.groupPerms,&permstr[4]);
        permtos3(file->perms.otherPerms,&permstr[7]);
        
        time_t timestamp = file->lastModified;
        struct tm* timeInfo=localtime(&timestamp);
        //printf("size of timeinfo: %lu, date: %d \n",sizeof(timeInfo),timeInfo.tm_mday);
        //timestampToTime(timestamp,&timeInfo);
        //printf("size of timeinfo: %lu, date: %d \n",sizeof(timeInfo),timeInfo.tm_mday);
        //printf("\nday: %d\n",(&timeInfo)->tm_mday);




        printf("%s   %lu   %s   %s   %lu   %d/%d/%d   %s\n",permstr,file->linkCount,file->ownerName,file->groupName,file->fileOrMetaSize,(timeInfo->tm_mon)+1,timeInfo->tm_mday,(timeInfo->tm_year)+1900,file->cleanedName);

    }
    else{
        //basicPrinter();
        printf("\n");
    }

}
