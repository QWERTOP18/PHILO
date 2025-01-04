#ifndef SYSTEM_H
# define SYSTEM_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define E_ALLOCATE 1
# define E_ARGS 2
# define E_FILE_READ 3

// typedef struct s_philo
// {
// 	long long		last_meal_time;
//     int             number_of_times_to_eat;
// }	t_philo;

typedef struct s_sys
{
	int				id;
	long long		last_meal_time;
	int				number_of_times_to_eat;
	pthread_t		daemon_thread;
	pthread_mutex_t	mutex_log;

	pid_t			*philo_pid;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	sem_t			*sem_fork;
	sem_t			sem_log;

}					t_sys;

void				system_exit(t_sys *sys, int status);
t_sys				*system_init(char **argv);

void				*__daemon(void *void_sys);

void				*__loop(t_sys *sys);

#endif
