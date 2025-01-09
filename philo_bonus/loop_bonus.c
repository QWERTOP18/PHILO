/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:19:53 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 11:05:33 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_bonus.h"
#include "system_bonus.h"
#include "utils_bonus.h"

int		praying(int id, t_sys *sys);
int		eating(int id, t_sys *sys);
int		sleeping(int id, t_sys *sys);
int		thinking(int id, t_sys *sys);

void	*__loop(t_sys *sys)
{
	sys->start_time = fetch_time();
	sys->last_meal_time = fetch_time();
	pthread_create(&sys->daemon_thread, NULL, __daemon, sys);
	pthread_detach(sys->daemon_thread);
	if (sys->id % 2 == 1)
		well_sleep(50);
	while (1)
	{
		if (praying(sys->id, sys) || eating(sys->id, sys))
		{
			exit(1);
		}
		sleeping(sys->id, sys);
		thinking(sys->id, sys);
	}
	return (NULL);
}

/* actuary they look for two mutex_forks */
int	praying(int id, t_sys *sys)
{
	int	status;

	sem_wait(sys->sem_log);
	status = sys->status;
	sem_post(sys->sem_log);
	if (status == TH_END)
		return (1);
	sem_wait(sys->sem_fork);
	sem_wait(sys->sem_fork);
	sem_wait(sys->sem_log);
	philo_log(id + 1, "has taken a fork", sys);
	sem_post(sys->sem_log);
	return (0);
}
// if (status == TH_THINKING)
// 	well_sleep(20);
// if (status == TH_HUNGRY)
// 	well_sleep(10);

int	eating(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	printf(CYAN);
	philo_log(id + 1, "is eating" RESET, sys);
	sys->last_meal_time = fetch_time();
	sys->number_of_times_to_eat++;
	sem_post(sys->sem_log);
	well_sleep(sys->time_to_eat);
	sem_post(sys->sem_fork);
	sem_post(sys->sem_fork);
	sem_wait(sys->sem_log);
	if (sys->status == TH_END)
	{
		sem_post(sys->sem_log);
		return (1);
	}
	sem_post(sys->sem_log);
	return (0);
}

int	sleeping(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	philo_log(id + 1, "is sleeping", sys);
	sem_post(sys->sem_log);
	well_sleep(sys->time_to_sleep);
	return (0);
}

int	thinking(int id, t_sys *sys)
{
	sem_wait(sys->sem_log);
	philo_log(id + 1, "is thinking", sys);
	sem_post(sys->sem_log);
	return (0);
}
