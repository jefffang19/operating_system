#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int is_pipe(int size, char **argv){
	for(int i=0;i<size;++i) if(strcmp(argv[i],"|") == 0) return 1;
	return 0;
}
int is_Rredirect(int size, char **argv){
	for(int i=0;i<size;++i) if(strcmp(argv[i],">") == 0) return 1;
	return 0;
}
int is_Lredirect(int size, char **argv){
	for(int i=0;i<size;++i) if(strcmp(argv[i],"<") == 0) return 1;
	return 0;
}
/* Note that first argument is num of tokens ,second argument should be original tokens*/
struct div_token * divide_token(int size, char **argv1){
	struct div_token* newArgvs = malloc(sizeof(newArgvs));
	newArgvs->right = malloc(sizeof(char*));
	int found = 0, cnt = 0;
	/* find | > < character */
	for(int i = 0; i < size; ++i){
		if(strcmp(argv1[i],"|") == 0 || strcmp(argv1[i],"<") == 0 || strcmp(argv1[i],">") == 0 ){
		found = i;
		continue;
		}
		/* copy to new argv */
		if(found){
			newArgvs->right[cnt] = malloc(sizeof(argv1[cnt]));
			memcpy(newArgvs->right[cnt],argv1[i],sizeof(argv1[cnt]));
			++cnt;
			newArgvs->right = (char*)realloc((void*)newArgvs->right,sizeof(char*)* (cnt+1));
		}
	}
	/* set the number of tokens on each side */
	newArgvs->nleft = found;
	newArgvs->nright = cnt;
	/* resize argv1 */
	char **argv1new = malloc(sizeof(char*)*found);
	for(int i = 0; i < found ; ++i){
		argv1new[i] = malloc(sizeof(argv1[i]));
		memcpy(argv1new[i],argv1[i],sizeof(argv1[i]));
	}
	newArgvs->left = argv1new;
	return newArgvs;
}
	
/* debug purpose */
/*
int main(){
	char *test1[5]={"echo","hello","|","xargs","echo"};
	struct div_token *newArgvs;
	printf("%d\n", sizeof(test1)/sizeof(char*));
	newArgvs = divide_token(5,test1);
	printf("test 1: %d\n",newArgvs->nleft);
	for(int i=0;i<newArgvs->nleft;++i) printf("%s\n",newArgvs->left[i]);
	printf("test 2: %d\n",newArgvs->nright);
	for(int i=0;i<newArgvs->nright;++i) printf("%s\n",newArgvs->right[i]);
	return 0;
}
*/
