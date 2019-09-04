// yanchen guo
// operating systems project 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// used to get the base name of a directory instead of the absolute path
#include <libgen.h>

// used to list all the files and sub-directories
#include <dirent.h>

// used to check file types
#include <sys/stat.h>
#include <sys/types.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

int isdirectory(char *path){
	struct stat statbuf;
	if(stat(path, &statbuf)== -1){
		printf("%s\n",path);
		return 0;
	}else{
		return S_ISDIR(statbuf.st_mode);
	}
}


int main(int argc, char *argv[]){
		
		char mycwd[PATH_MAX];
		if(getcwd(mycwd,PATH_MAX) == NULL){
			perror("Failed to get current working directory");
			return 1;
		}
	
		char *cwd = basename(mycwd);	
		printf("%s\n",cwd);
		

		struct dirent *de;  // Pointer for directory entry 
		DIR *dr = opendir(".");
		struct stat path_stat;
		char temp[PATH_MAX];
		char *path;

		while ((de = readdir(dr)) != NULL){
			//strcpy(temp,"/");
			//strcat(temp,de->d_name);	
			//printf("%s\n",temp);
			path = de->d_name;
			if(isdirectory(path)==0){
				//printf("no      %s  %s\n",de->d_name,de->d_type);
			}else if(strcmp(de->d_name,".")||strcmp(de->d_name,"..")){
			}else {
				printf("%s\n", de->d_name);
			}
		}
	
		closedir(dr);
		int argNum = argc-1;
		while(argNum > 0){
			if(strcmp(argv[argNum],"-h") == 0){
                        	perror("Help! -h has been called, terminating program.\n");
				return 1;
			}
			printf("hello we are in arg %d\n",argNum);
			argNum -=1;
		}
		return 0;
}
