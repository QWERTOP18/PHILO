/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:24:34 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 20:24:36 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"
#include <limits.h>
#include <string.h>

void	system_exit(t_sys *sys, int status)
{
	int	i;

	i = 0;
	if (sys && sys->philo_pid)
	{
		while (i < sys->number_of_philosophers)
		{
			kill(sys->philo_pid[i++], SIGKILL);
		}
		free(sys->philo_pid);
	}
	free(sys);
	if (status)
		printf("Error\n");
	exit(status);
}

t_sys	*system_init(char **argv)
{
	t_sys *sys;
	sys = (t_sys *)malloc(sizeof(t_sys));
	if (!sys)
		system_exit(sys, E_ALLOCATE);
	memset(sys, 0, sizeof(t_sys));
	sys->number_of_philosophers = fetch_number(*++argv, sys);
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

	return (sys);
}