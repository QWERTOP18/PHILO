/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:24:34 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 10:45:56 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"
#include <limits.h>
#include <string.h>

void	system_sem_init(t_sys *sys)
{
	sem_unlink("/fork_semaphore");
	sem_unlink("/log_semaphore");
	sys->sem_fork = sem_open("/fork_semaphore", O_CREAT, 0660,
			sys->number_of_philosophers);
	if (!sys->sem_fork)
		system_exit(sys, E_SEM_OPEN);
	sys->sem_log = sem_open("/log_semaphore", O_CREAT, 0660, 1);
	if (!sys->sem_log)
		system_exit(sys, E_SEM_OPEN);
}

void	system_sem_deinit(t_sys *sys)
{
	if (!sys)
		return ;
	sem_close(sys->sem_fork);
	sem_unlink("/fork_semaphore");
	sem_close(sys->sem_log);
	sem_unlink("/log_semaphore");
}

int	system_wait(t_sys *sys)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < sys->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status)
			break ;
		i++;
	}
	while (i < sys->number_of_philosophers)
	{
		waitpid(-1, &status, SIGTERM);
		i++;
	}
	return (0);
}

void	system_exit(t_sys *sys, int status)
{
	if (sys && sys->philo_pid)
	{
		free(sys->philo_pid);
	}
	system_sem_deinit(sys);
	free(sys);
	if (status)
		printf("Error\n");
	exit(status);
}

t_sys	*system_init(char **argv)
{
	t_sys	*sys;

	sys = (t_sys *)malloc(sizeof(t_sys));
	if (!sys)
		system_exit(sys, E_ALLOCATE);
	memset(sys, 0, sizeof(t_sys));
	sys->number_of_philosophers = fetch_number(*++argv, sys);
	system_sem_init(sys);
	if (sys->number_of_philosophers == 0)
		system_exit(sys, E_ALLOCATE);
	sys->time_to_die = fetch_number(*++argv, sys);
	sys->time_to_eat = fetch_number(*++argv, sys);
	sys->time_to_sleep = fetch_number(*++argv, sys);
	if (*++argv)
		sys->number_of_times_each_must_eat = fetch_number(*argv, sys);
	else
		sys->number_of_times_each_must_eat = INT_MAX;
	sys->philo_pid = malloc(sys->number_of_philosophers * sizeof(pid_t));
	if (!sys->philo_pid)
		system_exit(sys, E_ALLOCATE);
	if (!sys->number_of_times_each_must_eat)
		system_exit(sys, 0);
	return (sys);
}
