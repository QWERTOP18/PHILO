/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 10:06:05 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"

void	start_simulation(int i, t_sys *sys)
{
	while (i < sys->number_of_philosophers)
	{
		sys->id = i;
		sys->status = TH_STARVING;
		sys->philo_pid[i] = fork();
		if (sys->philo_pid[i] < 0)
			system_exit(sys, E_FORK);
		if (sys->philo_pid[i] == 0)
			__loop(sys);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_sys	*sys;

	if (argc != 5 && argc != 6)
		system_exit(NULL, E_ARGS);
	sys = system_init(argv);
	start_simulation(0, sys);
	system_exit(sys, system_wait(sys));
	return (0);
}
