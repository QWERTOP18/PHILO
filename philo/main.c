#include "system.h"

int	main(int argc, char **argv)
{
	t_sys	*sys;
	t_map	*map;
	int		i;

	if (argc != 5 && argc != 6)
		system_exit(NULL, E_ARGS);
	sys = system_init(argv);
	map = malloc(sizeof(t_map) * sys->number_of_philosophers);
	if (!map)
		system_exit(NULL, E_ALLOCATE);
	i = 0;
	pthread_create(&sys->daemon, NULL, __daemon, sys);
	while (i < sys->number_of_philosophers)
	{
		map[i].id = i;
		map[i].sys = sys;
		pthread_create(&sys->philos[i].thread, NULL, __loop, &map[i]);
		pthread_detach(sys->philos[i].thread);
		i++;
	}
	system_wait(sys);
	free(map);
	system_exit(sys, 0);
}
