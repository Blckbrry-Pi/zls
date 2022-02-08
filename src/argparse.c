#include<stdio.h>
#include<stdbool.h>
#include "argparse.h"

Argz parseArgz(int argc, char** argv){
	
	Argz argz = {0};

	argz.noPrintCharState = NO_PRINT_q;

	//printf("argc=%d\n", argc);
	//parsez argumentz
	if(argc>=1){
		//check for flagz
		int argzIndex;
		for (argzIndex=1; argzIndex<argc;argzIndex++) {
			char* pointer=argv[argzIndex];
			if(pointer[0]!='-'){
				break;
			}
			pointer++;
			//printf ("Parsing options, parse stanza %s\n", pointer);
			//printf("argz: -i: %d\n-A: %d\n-a: %d\n-l: %d\n-z: %d\n-Y: %d\n-1: %d\n-R: %d\n",argz.i,argz.A,argz.a,argz.l,argz.z,argz.Y,argz.one,argz.R);
			while(*pointer!='\0'){
				//printf("parse char %c in stanza\n", *pointer);
				switch(*pointer){
					case 'i':
						argz.i=true;
						break;
					case 'A':
						argz.A=true;
						break;
					case 'a':
						argz.a=true;
						break;
					case 'l':
						argz.l=true;
						break;
					case 'z':
						argz.z=true;
						break;
					case 'Y':
						argz.Y=true;
						break;
					case '1':
						argz.one=true;
						break;
					case 'R':
						argz.R=true;
						break;
					case 'B':
						argz.noPrintCharState = NO_PRINT_B;
						break;
					case 'b':
						argz.noPrintCharState = NO_PRINT_b;
						break;
					case 'w':
						argz.noPrintCharState = NO_PRINT_w;
						break;
					case 'q':
						argz.noPrintCharState = NO_PRINT_q;
						break;
				}
				//printf("argz: -i: %d\n-A: %d\n-a: %d\n-l: %d\n-z: %d\n-Y: %d\n-1: %d\n-R: %d\n",argz.i,argz.A,argz.a,argz.l,argz.z,argz.Y,argz.one,argz.R);
				//printf("flag -%c set\n",*pointer);
				pointer++;
			}
			
		}
		//no more flagz, parse filenamez
		if (argzIndex < argc) argz.file=argv[argzIndex];
		else argz.file = ".";
	}
	return argz;
}
