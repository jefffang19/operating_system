#include "ph.h"


void init(){
	pthread_mutex_init(&mutex,NULL);
	/* create THREAD_NUM thread */
    int i;
    for(i=0;i<THREAD_NUM;++i){
    	printf("Creat thread %d\n",i+1);
    	pthread_create(&philosopher[i],NULL,philo_routine,(void*)&i);
    }
    /* join thread */
    for(i=0;i<THREAD_NUM;++i){
    	pthread_join(philosopher[i],NULL);
    }
}
