/*
      3
   |      |
 4          2
   |      |
    5 | 1
*/
#ifndef PH_H
#define PH_H
#include <stdio.h>
#include <pthread.h>
#define THREAD_NUM 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philo_n+4) % THREAD_NUM
#define RIGHT (philo_n+1) % THREAD_NUM

int state[THREAD_NUM]; /* state of the philosopher */
pthread_t philosopher[THREAD_NUM];

pthread_mutex_t mutex; /* supervisor */

void try_to_eat(int philo_n);
void putdown(int philo_n);
void pickup(int philo_n);
void *philo_routine(void* philo_n);
void eating(int philo_n);
void become_hungry(int philo_n);
void debug();
#endif
