#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>


typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
    int             number_of_times_to_eat;
    int             is_dead;
	int				forks;
	pthread_t		thread;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*protection_mutex;
}	t_philo;




#endif