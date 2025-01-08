/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:39:37 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/08 20:02:27 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	main(int argc, char **argv)
{
	t_sys	*sys;
	t_map	*map;
	int		i;

	if (argc != 5 && argc != 6)
		system_exit(NULL, E_ARGS);
	sys = system_init(argv);
	if (!sys)
		return (0);
	map = malloc(sizeof(t_map) * sys->number_of_philosophers);
	if (!map)
		return (system_exit(NULL, E_ALLOCATE));
	i = 0;
	if (pthread_create(&sys->daemon, NULL, __daemon, sys))
		system_exit(sys, E_THREAD);
	while (i < sys->number_of_philosophers)
	{
		map[i].id = i;
		map[i].sys = sys;
		if (pthread_create(&sys->philos[i].thread, NULL, __loop, &map[i]))
			return (system_exit(sys, E_THREAD));
		i++;
	}
	system_exit(sys, 0);
	return (free(map), 0);
}
