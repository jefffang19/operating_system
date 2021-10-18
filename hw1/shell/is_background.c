#include <stdio.h>
#include "shell.h"

int is_background(int size, char ** myArgv) {

  	if (*myArgv == NULL)
    	return 0;
	/* look for & */
	for(int i=0;i<size;++i){
		if(strcmp(myArgv[i],"&")==0) return i;
	}
	return 0;
}

/* debug purpose */
/*
int main(){
	char *t[4] = {"a","b","c","&"};
	printf("%d\n",is_background(4,t));
	return 0;
}
*/
