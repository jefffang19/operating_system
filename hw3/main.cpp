#include "ph.h"

PDmonitor philo;

int main(){
	srand(time(NULL));
	philo.init();
	return 0;
}

void PDmonitor::init(){
	pthread_mutex_init(&mutex,NULL);
	int i, p[THREAD_NUM]={0,1,2,3,4};
	for(i=0;i<THREAD_NUM;++i)
		pthread_mutex_init(&(self_mutex[i]),NULL);
	/* create THREAD_NUM thread */
    for(i=0;i<THREAD_NUM;++i){
    	printf("Create thread %d\n",i+1);
    	pthread_create(&philosopher[i],NULL,philo_routine,&p[i]);
    }
    int j=0;
    /* join thread */
    for(j=0;j<THREAD_NUM;++j){
    	pthread_join(philosopher[j],NULL);
    }
}

void PDmonitor::try_to_eat(int philo_n){
	if(state[LEFT]!=EATING && state[RIGHT]!=EATING && state[philo_n]==HUNGRY){
		/* can eat (get two chopsticks) */
		state[philo_n] = EATING;
		show_state();
		pthread_cond_signal(&cond[philo_n]); //siganl wait
	}
}

void PDmonitor::putdown(int philo_n){
	//pthread_mutex_lock(&mutex);
	state[philo_n]=THINKING;
	show_state();
	try_to_eat(RIGHT);
	try_to_eat(LEFT);
	//pthread_mutex_unlock(&mutex);
	sleep(1);
}

void PDmonitor::pickup(int philo_n){
	//pthread_mutex_lock(&mutex);
	try_to_eat(philo_n);
	//pthread_mutex_unlock(&mutex);
	while(state[philo_n]==HUNGRY){
		pthread_mutex_lock(&self_mutex[philo_n]);
		pthread_cond_wait(&cond[philo_n],&self_mutex[philo_n]); //wait for signal
	}
	pthread_mutex_unlock(&self_mutex[philo_n]);
}

void PDmonitor::become_hungry(int philo_n){
	state[philo_n] = HUNGRY; /* say I am hungry */
	show_state();
}

void PDmonitor::eating(int philo_n){
	sleep(rand()%3+1);
}

void PDmonitor::show_state(){
	printf("Philosopher :");
	int i;
	for(i=0;i<5;++i){
		switch(state[i]){
			case 0:
				printf("T");
				break;
			case 1:
				printf("H");
				break;
			case 2:
				printf("E");
				break;
			default:
				fprintf(stderr,"error\n");
		}
		printf(" ");
	}
	printf("\n");
}

void* philo_routine(void* philo_n){
	int n = *((int*)philo_n);
	while(1){
		switch(philo.state[n]){
			case THINKING:
				philo.become_hungry(n); /* THINKING -> HUNGRY */
				break;
			case HUNGRY:
				philo.pickup(n); /* hungry -> try to pickup */
				break;
			case EATING:
				philo.eating(n); /* EATING */
				philo.putdown(n);
				break;
		}
	}
}
    
