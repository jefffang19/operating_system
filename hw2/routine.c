#include "ph.h"

void *philo_routine(void* philo_n){
	int n = *(int*)philo_n;
	usleep(50);
	while(1){
		switch(state[n]){
			case THINKING:
				become_hungry(n); /* THINKING -> HUNGRY */
				break;
			case HUNGRY:
				pickup(n); /* hungry -> try to pickup */
				break;
			case EATING:
				eating(n); /* EATING */
				putdown(n);
				break;
		}
	}
}
