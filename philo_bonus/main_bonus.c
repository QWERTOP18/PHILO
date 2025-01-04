/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/04 20:25:08 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"

int	main(int argc, char **argv)
{
	t_sys	*sys;
	int		i;
	int		status;

	if (argc != 5 && argc != 6)
		system_exit(NULL, E_ARGS);
	sys = system_init(argv);
	sem_unlink("/fork_semaphore");
	sem_unlink("/log_semaphore");
	sys->sem_fork = sem_open("/fork_semaphore", O_CREAT, 0660,
			sys->number_of_philosophers);
	sys->sem_log = sem_open("/log_semaphore", O_CREAT, 0660, 1);
	i = 0;
	while (i < sys->number_of_philosophers)
	{
		sys->id = i;
		sys->philo_pid[i] = fork();
		if (sys->philo_pid[i] == 0)
		{
			__loop(sys);
		}
		i++;
	}
	i = 0;
	status = 0;
	while (i < sys->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status)
			break ;
	}
	sem_close(sys->sem_fork);
	sem_unlink("/fork_semaphore");
	sem_close(sys->sem_log);
	sem_unlink("/log_semaphore");
	system_exit(sys, 0);
	return (0);
}
