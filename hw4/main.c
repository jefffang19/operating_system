#include <stdio.h>
#include "mm.h"

int main(){
	printf("test mymalloc\n");
	printf("int *a = (int*)mymalloc(sizeof(int));\n*a = 200;\n\n");
	int *a = (int*)mymalloc(sizeof(int));
	*a = 200;
	printf("value:%d\naddress:%p\n",*a,a);
	printf("\n\ntest mycalloc\n");
	printf("int *arr = (int*)mycalloc(10,sizeof(int));\nfor(i=0;i<10;++i) arr[i]=i;\n\n");
	int *arr = (int*)mycalloc(10,sizeof(int));
	int i;
	for(i=0;i<10;++i) arr[i]=i;
	for(i=0;i<10;++i){
		printf("value:%d address:%p\n",arr[i],&arr[i]);
	}
	printf("\n\ntest myrealloc\n");
	printf("arr = (int*)myrealloc(arr,20*sizeof(int));\nfor(i=0;i<20;++i) arr[i]=i;\n\n");
	arr = (int*)myrealloc(arr,20*sizeof(int));
	for(i=0;i<20;++i) arr[i]=i;
	for(i=0;i<20;++i){
		printf("value:%d address:%p\n",arr[i],&arr[i]);
	}
	return 0;
}
