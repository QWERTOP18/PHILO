#include "system.h"



void	*loop(void *void_map)
{

	t_map *map = (t_map *)void_map;
	if (map->id % 2 == 0)
		usleep(10);
	while (1)
	{
		praying(map->id, map->sys);
        eating(map->id, map->sys);
        sleeping(map->id, map->sys);
        thinking(map->id, map->sys);
	}
}




int main(int argc, char **argv)
{
    t_sys *sys;
    if (argc != 5 && argc != 6)
        system_exit(NULL, E_ARGS);
    sys = system_init(argc, argv);
    t_map *map = malloc(sizeof(t_map) * sys->number_of_philosophers);

    // Start the simulation
    int i = 0;
    while (i < sys->number_of_philosophers)
    {
        map[i].id = i;
        map[i].sys = sys;
        pthread_create(&sys->philos[i]->thread, NULL, loop, map);
        // pthread_detach(&sys->philos[i]->thread);
        i++;
    }

    //...
    // Wait for the simulation to finish
    i = 0;
    while (i < sys->number_of_philosophers)
    {
        pthread_join(sys->philos[i]->thread, NULL);
        i++;
    }
    free(map);
    system_exit(sys, 0);
}
