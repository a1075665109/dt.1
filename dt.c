// Yanchen Guo
// operating system
// project 1
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

// a recursive call with a path, space for indentation, level for subdirectory indentation and exeName for error
void depthfirst(char* root,int space, int level,char* exeName,int Lflag,int dflag,int iflag,int pflag,int sflag,int tflag,int uflag,int gflag){
	
	//create a dirent pointer and a file stat variable
	struct dirent *de;
	struct stat fileStat;
	
	// open the given directory and have a directory pointer points to the address
        
	DIR *dr = opendir(root);
	int a;
	
	// if the directory it is not a directory, return;
	if(!dr){
		//printf("not directory\n");
		return;
	}else{
		//printf("directory\n");
	

	// loop through the directory for each file within that directory
	// indent each file with the given or default space
	while ((de = readdir(dr)) != NULL){	
		// if statment that skips through directory . and .. and .git
		if(strcmp(de->d_name,".git")==0||strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0){		
		}else{
			int s = space*level;
			while(s>0){
				printf(" ");
				s-=1;
			}
			
		// store filestate in the filestate variable address based on the given file name de->d_name
		a =stat(de->d_name,&fileStat);
		printf("%-30s", de->d_name);
		char numOfLinks[PATH_MAX];
		char fileSize[PATH_MAX];

		//////////////////////////////////// -s command for filesize  ////////////////////////////////
		if(sflag == 1){

		// if the file size is greater than 1kb and less than 1mb	
		if (fileStat.st_size>=1000&&fileStat.st_size<1000000){
        	        sprintf(fileSize, "%d",fileStat.st_size/1000);
			strcat(fileSize,"K");
			printf("%-15s",fileSize);
		
		// if the file size is greater than 1mb and less than 1gb
		}else if(fileStat.st_size>=1000000&&fileStat.st_size<1000000000){
                        sprintf(fileSize, "%d",fileStat.st_size/1000000000);
                        strcat(fileSize,"M");
                        printf("%-15s",fileSize);
	
		// if the file size is greater than 1gb
		}else if (fileStat.st_size >=1000000000){
	                sprintf(fileSize, "%d",fileStat.st_size/1000000000);
                        strcat(fileSize,"G");
                        printf("%-15s",fileSize);	
		// if the file size is less than 1kb
		}else{
                	sprintf(fileSize, "%d",fileStat.st_size);
			printf("%-15s",fileSize);
		}
		}
		
		 //////////////////////////////////// -t command for file type  ////////////////////////////////
	
		if(tflag ==1){
			printf("FileType: ");
			switch(fileStat.st_mode &S_IFMT){
				case S_IFDIR:	printf("d");  break;
				case S_IFLNK:   printf("l");  break;
				case S_IFREG:	printf("f"); break;
				case S_IFBLK:	printf("b"); break;
				case S_IFCHR:	printf("c"); break;
				default: printf("f"); break;
			}
			printf("%-15s"," ");
		}
		
		 //////////////////////////////////// -p command for file permission  ////////////////////////////////
		
		if(pflag ==1){
			printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
			printf("%-15s"," ");
		}

		 //////////////////////////////////// -i command for number of links  ////////////////////////////////
		
		if(iflag ==1){
			sprintf(numOfLinks, "%d",fileStat.st_nlink);
			strcat(numOfLinks,"links");
			printf("%-15s",numOfLinks);
		}
		 //////////////////////////////////// -u command for userID  ////////////////////////////////

		if(uflag ==1){
			printf("Uid: ");
			printf("%-10d",fileStat.st_uid);
			printf("%-10s",getenv("USER"));
		}
		 //////////////////////////////////// -g command for groupID  ////////////////////////////////
		
		if(gflag ==1){
			printf("Gid: ");
			printf("%-10d",fileStat.st_gid);
	        }
		 //////////////////////////////////// -d command for last day of mod  ////////////////////////////////
		
		if(dflag ==1){
			char mtime[80];
			time_t t = fileStat.st_mtime;
			struct tm lt;
    			localtime_r(&t, &lt); /* convert to struct tm */
    			strftime(mtime, sizeof mtime, "%b %d, %Y ", &lt);
    			printf("%-10s", mtime);
		}
			// recursive calls everytime a file is reached, returned at the top if file is not a directory.
			printf("\n");
			depthfirst(de->d_name,space,level+1,exeName,Lflag,dflag,iflag,pflag,sflag,tflag,uflag,gflag);
		}
	}
	closedir(dr);
	}
}


int main(int argc, char* argv[]){
	int index;
	char* symLink;
	// option for different arguments, line space for -I
	int opt;
	int lineSpace = 4;
	// set the default directory to the current directory
	char* curDir = ".";

	// flags to pass in to the traversal function, could be set as global
	int hflag=0,Lflag=0,dflag=0,gflag=0,iflag=0,pflag=0,sflag=0,tflag=0,uflag=0,lflag=0;
	
	// getopt loop to help sorting arguments given by the user.
	// stop on -h command and command I sets the line spacing.
	// set the flags to 1 if command argument is called
	while((opt = getopt(argc,argv,":hI:L:dgipstul"))!=-1){
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
				printf("symbolic link: %s\n",optarg);
				Lflag = 1;
				curDir = optarg;
				break;
			case 'd':
				dflag = 1;
				break;
			case 'i':
				iflag = 1;
				break;
			case 'p':
				pflag = 1;
				break;
			case 's':
				sflag = 1;
				break;
			case 't':
				tflag = 1;
				break;
			case 'u':
				uflag = 1;
				break;
			case 'g':
				gflag = 1;
				break;
			case 'l':
				tflag =1;
				pflag =1;
				iflag =1;
				uflag =1;
				gflag =1;
				sflag =1;
				break;
			case '?':

				perror("Unkown option");
				break;
		}
	}
	
	// if there are left over command line arguments, print them out as error or seen as a directory given
	if(argv[optind]!=NULL){
        curDir = argv[optind];
	}
	
	// call the traversal function with the directory, linespacing, the executable name argv[0], and all the flags.
	depthfirst(curDir,lineSpace,1,argv[0],Lflag,dflag,iflag,pflag,sflag,tflag,uflag,gflag);
	return 0;
}
























