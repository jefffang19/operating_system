#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>


int main(){
	int fd = open("text", O_RDONLY);
	
	struct stat file_status = {0}; 								
	fstat(fd, &file_status);
	
	char *map = (char*)mmap(0, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);
	
	close(fd);
	
	while(file_status.st_size){
	
		char cmd;

		printf("enter 'q' to exit, 'c' to continue\n");
		scanf("%c", &cmd);
		if(cmd == 'q') break;
		scanf("%c", &cmd); // filt the '\n'

		int i = 0; // flow control
		for(i=0;i<getpagesize();i++){
			printf("%c", map[i]);
		}
		
	}
	
	return 0;
}
