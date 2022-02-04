#include "colors.h"

const char *fi = "\x1b[0m";
const char *di = "\x1b[0;1;34m";
const char *ex = "\x1b[0;1;32m";
const char *ln = "\x1b[0;1;36m";
const char *or = "\x1b[0;40;1;31m";
const char *mh = "\x1b[0;1m";
const char *pi = "\x1b[0;40;33m";
const char *so = "\x1b[0;1;35m";
const char *bd = "\x1b[0;40;1;33m";

const char *getEntryColor(FileInfo *f) {
    switch (f->fileType) {
        case FT_REG: {
            if (f->linkCount > 1) return mh;
            else if ((f->perms.ownerPerms | f->perms.groupPerms | f->perms.otherPerms) & 1)  return ex;
            else return fi;
        }

        case FT_DIR:
            return di;

        case FT_LINK:
            if (0) return or; // TODO: make this detect a broken symlink.
            else return ln;

        case FT_FIFO:
            return pi;

        case FT_SOCK:
        case FT_DOOR:
            return so;

        case FT_BLCK:
        case FT_CHAR:
            return bd;

    }
    return "";
}
