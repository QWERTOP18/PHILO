#include "system.h"



void	*__loop(void *void_map)
{
	t_map *map = (t_map *)void_map;
	if (map->id % 2 == 0)
		usleep(10);
    printf("id = %d\n",map->id);
	while (1)
	{
		praying(map->id, map->sys);
        eating(map->id, map->sys);
        sleeping(map->id, map->sys);
        thinking(map->id, map->sys);
	}
    return NULL;
}

void   *__daemon(void *void_sys)
{
    t_sys *sys = (t_sys *)void_sys;
    while (1)
    {
        if (check_is_satisfy(sys))
            return NULL;
        if (check_is_dead(sys))
            return NULL;
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

     #ifdef LOG
    printf("main simulation\n");
    #endif
    int i = 0;
    while (i < sys->number_of_philosophers)
    {
        map[i].id = i;
        map[i].sys = sys;
        pthread_create(&sys->philos[i]->thread, NULL, __loop, &map[i]);
        // pthread_detach(&sys->philos[i]->thread);
        i++;
    }

    pthread_t daemon_thread;
    pthread_create(&daemon_thread, NULL, __daemon, sys);
    i = 0;
    while (i < sys->number_of_philosophers)
    {
        pthread_join(sys->philos[i]->thread, NULL);
        i++;
    }
    free(map);
    system_exit(sys, 0);
    return 0;
}
