
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

void depthfirst(char* root,int level){
	  char mycwd[PATH_MAX];
                if(getcwd(mycwd,PATH_MAX) == NULL){
                        perror("Failed to get current working directory");
                        return 1;
                }

                char *cwd = basename(mycwd);
                printf("%s\n",cwd);

}


int main(int argc, char* argv[]){
	int index;
	int opt;
	while((opt = getopt(argc,argv,":hI:Ldgipstul"))!=-1){
		switch(opt){
			case 'h':
				printf("-h command has been called, program terminated!\n");
				return 0;	
				break;
			case 'I':
				printf("Line spacing: %s\n",optarg);
				break;
			case 'L':

				break;
			case 'd':
				
				break;
			case 'g':
				
				break;
			case 'i':

				break;
			case 'p':

				break;
			case 's':

				break;
			case 't':

				break;
			case 'u':

				break;
			case 'l':

				break;
			case '?':

				printf("Unkown option %c\n", optopt);
				break;
		}
	}
	if(argv[optind]!=NULL){
	printf("Directory name: %s\n",argv[optind]);
	}
	return 0;
}
