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
	// int				id;
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
    pthread_mutex_t	mutex_log;
} t_sys;

typedef struct s_map
{
    int id;
    t_sys *sys;
} t_map;



// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// ◦ number_of_philosophers: The number of philosophers and also the number of forks.
// ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
// ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
// ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
// ◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.


void system_exit(t_sys *sys, int status);

t_sys *system_init(int argc, char **argv);




void	praying(int id, t_sys *sys);
void	eating(int id, t_sys *sys);

void	sleeping(int id, t_sys *sys);

void	thinking(int id, t_sys *sys);


#endif

