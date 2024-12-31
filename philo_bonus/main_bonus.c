#include "system_bonus.h"


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
    pthread_t daemon_thread;
    pthread_create(&daemon_thread, NULL, __daemon, sys);
    while (i < sys->number_of_philosophers)
    {
        map[i].id = i;
        map[i].sys = sys;
        pthread_create(&sys->philos[i]->thread, NULL, __loop, &map[i]);
        pthread_detach(sys->philos[i]->thread);
        i++;
    }
    #ifdef LOG
    printf("main done\n");
    #endif
    i = 0;
    // while (i < sys->number_of_philosophers)
    // {
    //     pthread_join(sys->philos[i]->thread, NULL);
    //     i++;
    // }
    pthread_detach(daemon_thread);
    free(map);
    #ifdef LOG
    printf("main done\n");
    #endif
    system_exit(sys, 0);
    return 0;
}
