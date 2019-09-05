
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
	
	//create a dirent pointer and a file stat variable
	struct dirent *de;
	struct stat fileStat;
	
	// open the given directory and have a directory pointer points to the address
        DIR *dr = opendir(root);

	// if the directory is null, give an error
	if(dr ==NULL){
		printf("%s: Error: ",exeName);
		perror("");
	}

	// loop through the directory for each file within that directory
	// indent each file with the given or default space
	while ((de = readdir(dr)) != NULL){
		int s = space;
		while(s>0){
			printf(" ");
			s-=1;
		}
	
		// store filestate in the filestate variable address based on the given file name de->d_name
		stat(de->d_name,&fileStat);
		printf("%-25s", de->d_name);
		
		char fileSize[255];
		// if the file size is greater than 1kb and less than 1mb	
		if (fileStat.st_size>=1000&&fileStat.st_size<1000000){
        	        sprintf(fileSize, "%d",fileStat.st_size/1000);
			strcat(fileSize,"KB");
			printf("%-15s",fileSize);
		
		// if the file size is greater than 1mb and less than 1gb
		}else if(fileStat.st_size>=1000000&&fileStat.st_size<1000000000){
                        sprintf(fileSize, "%d",fileStat.st_size/1000000000);
                        strcat(fileSize,"MB");
                        printf("%-15s",fileSize);
	
		// if the file size is greater than 1gb
		}else if (fileStat.st_size >=1000000000){
	                sprintf(fileSize, "%d",fileStat.st_size/1000000000);
                        strcat(fileSize,"GB");
                        printf("%-15s",fileSize);	
		// if the file size is less than 1kb
		}else{
                	sprintf(fileSize, "%d",fileStat.st_size);
                        strcat(fileSize,"bytes");
			printf("%-15s",fileSize);
		}

		// print uid, gid and the time using stat functions, convert the time into correct format
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

	// option for different arguments, line space for -I
	int opt;
	int lineSpace = 4;
	// set the default directory to the current directory
	char* curDir = ".";

	// getopt loop to help sorting arguments given by the user.
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
				depthfirst(curDir,lineSpace,1,argv[0]);			
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
	// if there are left over command line arguments, print them out as error or seen as a directory given
	if(argv[optind]!=NULL){
	printf("Directory name: %s\n",argv[optind]);
	}
	return 0;
}
