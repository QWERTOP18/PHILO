#include "system_bonus.h"
#include "utils_bonus.h"




int main(int argc, char **argv)
{
    t_sys *sys;
    if (argc != 5 && argc != 6)
        system_exit(NULL, E_ARGS);
    sys = system_init(argv);

    sem_init(&sys->sem_fork, 0, sys->number_of_philosophers);
    int i = 0;
    while (i < sys->number_of_philosophers)
    {
        sys->id = i;
        sys->philo_pid[i] =  fork();
        if (sys->philo_pid[i] == 0)
        {
            __loop(sys);
        }

        i++;
    }
    i = 0;
    int status = 0;
    while (i < sys->number_of_philosophers)
    {
        waitpid(sys->philo_pid[i], &status, 0);
        if (status)
        {
            philo_log(i+1,"died",sys);
            break;
        }
        i++;
    }
    sem_destroy(&sys->sem_fork);
    #ifdef LOG
    printf("main done\n");
    #endif
    system_exit(sys, 0);
    return 0;
}
