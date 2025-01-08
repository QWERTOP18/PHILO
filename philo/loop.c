/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:39:28 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/08 23:10:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include "utils.h"

int		praying(int id, t_sys *sys);
int		eating(int id, t_sys *sys);
int		sleeping(int id, t_sys *sys);
int		thinking(int id, t_sys *sys);

void	*__loop(void *void_map)
{
	t_sys	*sys;
	int		id;
	int		nid;

	sys = ((t_map *)void_map)->sys;
	id = ((t_map *)void_map)->id;
	nid = (id + 1) % sys->number_of_philosophers;
	if (id % 2 == 1)
		well_sleep(20 * id);
	while (1)
	{
		if (praying(id, sys) || eating(id, sys))
		{
			pthread_mutex_unlock(&sys->philos[nid].mutex_fork);
			pthread_mutex_unlock(&sys->philos[id].mutex_fork);
			pthread_mutex_unlock(&sys->mutex_log);
			return (NULL);
		}
		if (sleeping(id, sys) || thinking(id, sys))
		{
			pthread_mutex_unlock(&sys->mutex_log);
			return (NULL);
		}
	}
	return (pthread_mutex_unlock(&sys->philos[id].mutex_fork), NULL);
}

/* actuary they look for two mutex_forks */
// pthread_mutex_lock(&sys->philos[id].mutex_fork);
// pthread_mutex_lock(&sys->philos[nid].mutex_fork);
int	praying(int id, t_sys *sys)
{
	int	nid;

	nid = (id + 1) % sys->number_of_philosophers;
	if (id < nid)
	{
		pthread_mutex_lock(&sys->philos[id].mutex_fork);
		pthread_mutex_lock(&sys->philos[nid].mutex_fork);
	}
	else
	{
		pthread_mutex_lock(&sys->philos[nid].mutex_fork);
		pthread_mutex_lock(&sys->philos[id].mutex_fork);
	}
	pthread_mutex_lock(&sys->mutex_log);
	if (philo_log(id + 1, "has taken a fork", sys))
		return (1);
	pthread_mutex_unlock(&sys->mutex_log);
	return (0);
}

int	eating(int id, t_sys *sys)
{
	int	nid;

	nid = (id + 1) % sys->number_of_philosophers;
	pthread_mutex_lock(&sys->mutex_log);
	if (philo_log(id + 1, CYAN "is eating" RESET, sys))
		return (1);
	sys->philos[id].last_meal_time = fetch_time();
	sys->philos[id].number_of_times_to_eat++;
	pthread_mutex_unlock(&sys->mutex_log);
	well_sleep(sys->time_to_eat);
	pthread_mutex_unlock(&sys->philos[nid].mutex_fork);
	pthread_mutex_unlock(&sys->philos[id].mutex_fork);
	return (0);
}

int	sleeping(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->mutex_log);
	if (philo_log(id + 1, "is sleeping", sys))
		return (1);
	pthread_mutex_unlock(&sys->mutex_log);
	well_sleep(sys->time_to_sleep);
	return (0);
}

int	thinking(int id, t_sys *sys)
{
	pthread_mutex_lock(&sys->mutex_log);
	if (philo_log(id + 1, "is thinking", sys))
		return (1);
	pthread_mutex_unlock(&sys->mutex_log);
	return (0);
}
