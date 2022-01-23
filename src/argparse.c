#include<stdio.h>
#include<stdbool.h>
#include "argparse.h"

Args parseArgz(int argc, char** argv){
	
	Args argz;

	printf("argc=%d\n", argc);
	//parsez argumentz
	if(argc>=1){
		//check for flagz
		int argzIndex;
		for (argzIndex=1; argzIndex<argc;argzIndex++){
			char* pointer=argv[argzIndex];
			if(pointer[0]!='-'){
				break;
			}
			pointer++;
			while(*pointer!='\0'){
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
				}

				printf("flag -%c set\n",*pointer);
				pointer++;
			}
			
		}
		//no more flagz, parse filenamez
			argz.file=argv[argzIndex];

		
	}
}