

#include "system_bonus.h"
#include "utils_bonus.h"

void	praying(int id, t_sys *sys);
void	eating(int id, t_sys *sys);
void	sleeping(int id, t_sys *sys);
void	thinking(int id, t_sys *sys);

void	*__loop(t_sys *sys)
{
	// if (map->id % 2 == 0)
	// 	usleep(10);
	pthread_create(&sys->daemon_thread, NULL, __daemon, sys);
	while (1)
	{
		praying(sys->id, sys);
        eating(sys->id, sys);
        sleeping(sys->id, sys);
        thinking(sys->id, sys);
	}
	pthread_detach(sys->daemon_thread);
    return NULL;
}


/* actuary they look for two mutex_forks */
void	praying(int id, t_sys *sys)
{
    sem_wait(&sys->sem_fork);  
    sem_wait(&sys->sem_fork);  
	philo_log(id+1, "has taken a fork",sys);
	
}

void	eating(int id, t_sys *sys)
{
	philo_log(id+1, "is eating",sys);
	
	sys->last_meal_time = fetch_time();
	sys->number_of_times_to_eat++;
	
	well_sleep(sys->time_to_eat);
	sem_post(&sys->sem_fork);
	sem_post(&sys->sem_fork);
}

void	sleeping(int id, t_sys *sys)
{
	philo_log(id+1, "is sleeping",sys);
	well_sleep(sys->time_to_sleep);
}

void	thinking(int id, t_sys *sys)
{
	philo_log(id+1, "is thinking",sys);
}

