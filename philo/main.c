#include "system.h"


int main(int argc, char **argv)
{
    t_sys *sys;
    if (argc != 5 && argc != 6)
        system_exit(NULL, E_ARGS);
    sys = system_init(argc, argv);
    t_map *map = malloc(sizeof(t_map) * sys->number_of_philosophers);
    if (!map)
        system_exit(NULL, E_ALLOCATE);

    int i;
    i = 0;
    pthread_create(&sys->daemon ,NULL, __daemon, sys);
    while (i < sys->number_of_philosophers)
    {
        map[i].id = i;
        map[i].sys = sys;
        //startt_timeはここに設定する方が良いか　todo
        pthread_create(&sys->philos[i]->thread, NULL, __loop, &map[i]);
        pthread_detach(sys->philos[i]->thread);
        pthread_mutex_destroy(&sys->philos[i]->mutex_fork);
        i++;
    }
    pthread_detach(sys->daemon);
    pthread_mutex_destroy(&sys->mutex_log);
    free(map);
    system_exit(sys, 0);
}
