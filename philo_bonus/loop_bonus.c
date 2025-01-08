/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:19:53 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/08 22:56:15 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"

void	praying(int id, t_sys *sys);
void	eating(int id, t_sys *sys);
void	sleeping(int id, t_sys *sys);
void	thinking(int id, t_sys *sys);

void	*__loop(t_sys *sys)
{
	sys->start_time = fetch_time();
	sys->last_meal_time = fetch_time();
	pthread_create(&sys->daemon_thread, NULL, __daemon, sys);
	pthread_detach(sys->daemon_thread);
	if (sys->id % 2 == 1)
		well_sleep(10);
	while (1)
	{
		praying(sys->id, sys);
		eating(sys->id, sys);
		sleeping(sys->id, sys);
		thinking(sys->id, sys);
	}
	return (NULL);
}

/* actuary they look for two mutex_forks */
void	praying(int id, t_sys *sys)
{
	sem_wait(sys->sem_fork);
	sem_wait(sys->sem_fork);
	sem_wait(sys->sem_log);
	philo_log(id + 1, "has taken a fork", sys);
	sem_post(sys->sem_log);
}

void	eating(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	philo_log(id + 1, "is eating", sys);
	sys->last_meal_time = fetch_time();
	sys->number_of_times_to_eat++;
	sem_post(sys->sem_log);
	well_sleep(sys->time_to_eat);
	sem_post(sys->sem_fork);
	sem_post(sys->sem_fork);
}

void	sleeping(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	philo_log(id + 1, "is sleeping", sys);
	sem_post(sys->sem_log);
	well_sleep(sys->time_to_sleep);
}

void	thinking(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	philo_log(id + 1, "is thinking", sys);
	sem_post(sys->sem_log);
}
