

#include "system.h"



/* actuary they look for two forks */
void	praying(int id, t_sys *sys)
{
    int nid = (id + 1) % sys->number_of_philosophers;
	pthread_mutex_lock(&sys->philos[id]->fork);
	pthread_mutex_lock(&sys->philos[nid]->fork);
	pthread_mutex_lock(&sys->log);
	philo_log(id+1, "has taken a fork",sys);
	pthread_mutex_unlock(&sys->log);
}

void	eating(int id, t_sys *sys)
{
    int nid = (id + 1) % sys->number_of_philosophers;

	pthread_mutex_lock(&sys->log);
	philo_log(id+1, "is eating",sys);
	
	sys->philos[id]->last_meal_time = fetch_time();
	sys->philos[id]->number_of_times_to_eat++;
	pthread_mutex_unlock(&sys->log);
	usleep(sys->time_to_eat);
	pthread_mutex_unlock(&sys->philos[id]->fork);
	pthread_mutex_unlock(&sys->philos[nid]->fork);
}

void	sleeping(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->log);
	philo_log(id+1, "is sleeping",sys);
	pthread_mutex_unlock(&sys->log);
	usleep(sys->time_to_sleep);
}

void	thinking(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->log);
	philo_log(id+1, "is thinking",sys);
	pthread_mutex_unlock(&sys->log);
}
