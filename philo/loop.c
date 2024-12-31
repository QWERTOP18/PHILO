

#include "system.h"
#include "utils.h"

void	praying(int id, t_sys *sys);
void	eating(int id, t_sys *sys);
void	sleeping(int id, t_sys *sys);
void	thinking(int id, t_sys *sys);

void	*__loop(void *void_map)
{
	t_map *map = (t_map *)void_map;
	// if (map->id % 2 == 0)
	// 	usleep(10);
	while (1)
	{
		praying(map->id, map->sys);
        eating(map->id, map->sys);
        sleeping(map->id, map->sys);
        thinking(map->id, map->sys);
	}
    return NULL;
}


/* actuary they look for two mutex_forks */
void	praying(int id, t_sys *sys)
{
    int nid = (id + 1) % sys->number_of_philosophers;
	pthread_mutex_lock(&sys->philos[id]->mutex_fork);
	pthread_mutex_lock(&sys->philos[nid]->mutex_fork);
	pthread_mutex_lock(&sys->mutex_log);
	philo_log(id+1, "has taken a fork",sys);
	pthread_mutex_unlock(&sys->mutex_log);
}

void	eating(int id, t_sys *sys)
{
    int nid = (id + 1) % sys->number_of_philosophers;

	pthread_mutex_lock(&sys->mutex_log);
	philo_log(id+1, "is eating",sys);
	
	sys->philos[id]->last_meal_time = fetch_time();
	sys->philos[id]->number_of_times_to_eat++;
	pthread_mutex_unlock(&sys->mutex_log);
	well_sleep(sys->time_to_eat);
	pthread_mutex_unlock(&sys->philos[id]->mutex_fork);
	pthread_mutex_unlock(&sys->philos[nid]->mutex_fork);
}

void	sleeping(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->mutex_log);
	philo_log(id+1, "is sleeping",sys);
	pthread_mutex_unlock(&sys->mutex_log);
	well_sleep(sys->time_to_sleep);
}

void	thinking(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->mutex_log);
	philo_log(id+1, "is thinking",sys);
	pthread_mutex_unlock(&sys->mutex_log);
}

