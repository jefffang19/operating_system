#include "ph.h"

void try_to_eat(int philo_n){
	if(state[LEFT]!=EATING && state[RIGHT]!=EATING && state[philo_n]==HUNGRY){
		/* can eat (get two chopsticks) */
		state[philo_n] = EATING;
		debug();
	}
}

void putdown(int philo_n){
	pthread_mutex_lock(&mutex);
	usleep(500);
	state[philo_n]=THINKING;
	debug();
	try_to_eat(RIGHT);
	try_to_eat(LEFT);
	pthread_mutex_unlock(&mutex);
}

void pickup(int philo_n){
	pthread_mutex_lock(&mutex);
	try_to_eat(philo_n);
	pthread_mutex_unlock(&mutex);
}

void become_hungry(int philo_n){
	state[philo_n] = HUNGRY; /* say I am hungry */
	debug();
	sleep(2);
}

void eating(int philo_n){
	/*printf("Philosopher %d is eating\n",philo_n);*/
	sleep(3);
}

void debug(){
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
				fprintf(stderr,"error");
		}
		printf(" ");
	}
	printf("\n");
}
