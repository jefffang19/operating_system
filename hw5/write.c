#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1000

int main(){
	int fd = 0;
	fd = open("text", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	
	struct stat file_status = {0};
	fstat(fd, &file_status);
	
	char *map = (char*)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, 0);
	
	char line[SIZE];
	
	printf("input: ");
	while(fgets(line, SIZE, stdin)){
		
		lseek(fd, file_status.st_size + strlen(line), SEEK_SET);
		write(fd, "", 1);
		lseek(fd, 0, SEEK_SET);
	
		int i=0;
		for(i=0;i<strlen(line);i++){
	
			map[file_status.st_size + i] = line[i];
		}
		file_status.st_size += strlen(line);
		
		printf("input: ");
	}
	close(fd);
	
	return 0;
}
