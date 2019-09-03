// yanchen guo
// operating systems project 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
		if(strcmp(argv[1],"-h") == 0){
			printf("Help! -h has been called\n");
		}
		printf ("new project %s\n %s \n",argv[0],argv[1]);
		return 0;		
}
