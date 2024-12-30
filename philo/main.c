#include "system.h"



void	*loop(void *v_sys)
{

	t_sys *sys = (t_sys*)v_sys;
	if (sys->cur_id % 2 == 0)
		usleep(10);
	while (1)
	{
		praying(sys->cur_id,sys);
        eating(sys->cur_id,sys);
        sleeping(sys->cur_id,sys);
        thinking(sys->cur_id,sys);
	}
}




int main(int argc, char **argv)
{
    t_sys *sys;
    if (argc != 5 && argc != 6)
        system_exit(NULL, E_ARGS);
    sys = system_init(argc, argv);
    // Start the simulation
    int i = 0;
    while (i < sys->number_of_philosophers)
    {
        pthread_create(&sys->philos[i]->thread, NULL, loop, sys);
        pthread_detach(&sys->philos[i]->thread);
        i++;
    }

    //...
    system_exit(sys, 0);
}
