/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 20:15:05 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_bonus.h"
#include "utils_bonus.h"

int	main(int argc, char **argv)
{
	t_sys	*sys;
	int		i;

	if (argc != 5 && argc != 6)
		system_exit(NULL, E_ARGS);
	sys = system_init(argv);
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
	system_exit(sys, system_wait(sys));
	return (0);
}
