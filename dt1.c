
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h> 
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

void depthfirst(char* root,int space, int level,char* exeName){
	struct dirent *de;
	struct stat fileStat;
        DIR *dr = opendir(root);
	if(dr ==NULL){
		printf("%s: Error: ",exeName);
		perror("");
		exit(0);
	}
	while ((de = readdir(dr)) != NULL){
		int s = space;
		while(s>0){
			printf(" ");
			s-=1;
		}
		stat(de->d_name,&fileStat);
		printf("%-25s", de->d_name);
		printf("FileSize: ");
		printf("%-10d",fileStat.st_size);
		printf("Uid: ");
		printf("%-10d",fileStat.st_uid);
		printf("Pid: ");
		printf("%-10d",fileStat.st_gid);
	        char mtime[80];
		time_t t = fileStat.st_mtime;
		struct tm lt;
    		localtime_r(&t, &lt); /* convert to struct tm */
    		strftime(mtime, sizeof mtime, "%b %d, %Y ", &lt);
    		printf("%-10s\n", mtime);
		}	
	closedir(dr);
}


int main(int argc, char* argv[]){
	int index;
	int opt;
	int lineSpace;
	while((opt = getopt(argc,argv,":hI:Ldgipstul"))!=-1){
		switch(opt){
			case 'h':
				printf("-h command has been called, program terminated!\n");
				return 0;	
				break;
			case 'I':
				printf("Line spacing: %s\n",optarg);
				lineSpace =atoi(optarg);
				break;
			case 'L':

				break;
			case 'd':
	
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
				depthfirst("./",lineSpace,1,argv[0]);			
				break;
			case 'g':
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
