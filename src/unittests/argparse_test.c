#include "../argparse.h"

#include <stdio.h>

int main(int argc,char** argv) {
    Argz argz=parseArgz(argc,argv);
    printf("\nargz: \n-i: %d\n-A: %d\n-a: %d\n-l: %d\n-z: %d\n-Y: %d\n-1: %d\n-R: %d\n",argz.i,argz.A,argz.a,argz.l,argz.z,argz.Y,argz.one,argz.R);
    printf("filename: %s",argz.file);
    return 0;
}
