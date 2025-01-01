#ifndef SYSTEM_H
#define SYSTEM_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

#include "color.h"



#define E_ALLOCATE 1
#define E_ARGS 2
#define E_FILE_READ 3


typedef struct s_philo
{
	long long		last_meal_time;
    int             number_of_times_to_eat;
	pthread_t		thread;
    pthread_mutex_t    mutex_fork;
	
}	t_philo;

typedef struct s_sys
{
    t_philo        **philos;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start_time;
    pthread_t daemon;
    pthread_mutex_t	mutex_log;
} t_sys;

typedef struct s_map
{
    int id;
    t_sys *sys;
} t_map;


void system_exit(t_sys *sys, int status);
t_sys *system_init(int argc, char **argv);

void   *__daemon(void *void_sys);

void	*__loop(void *void_map);


#endif

