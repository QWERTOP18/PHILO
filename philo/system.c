#include "system.h"
#include "utils.h"
#include <string.h>



void system_exit(t_sys *sys, int status)
{
    int i = 0;
    if (sys && sys->philos)
    {
        while (sys->philos[i])
        {
            free(sys->philos[i]);
            sys->philos[i] = NULL;
            i++;
        }
        free(sys->philos);
        sys->philos = NULL;
    }
    free(sys);
    if(status)
        printf("Error\n");
    exit(status);
}

void give_birth(int num, t_sys *sys)
{
    sys->philos = malloc(sizeof(t_philo *) * (num+1));
    memset(sys->philos, 0, sizeof(t_philo *) * (num+1));
    int i;
    i = 0;
    while (i < num)
    {
        sys->philos[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!sys->philos[i])
            system_exit(sys, 1);
        sys->philos[i]->id = i;
       // sys->philos[i]->last_meal_time = (long long *)malloc(sizeof(long long));
        sys->philos[i]->last_meal_time = sys->born_time;
        sys->philos[i]->number_of_times_to_eat = 0;
        sys->philos[i]->is_dead = 0;
        sys->philos[i]->forks = (i + 1) % num;
        i++;
    }
}

t_sys *system_init(int argc, char **argv)
{
    t_sys *sys;

    sys = NULL;
    if (argc != 5 && argc != 6)
        system_exit(sys, E_ARGS);
    sys = (t_sys *)malloc(sizeof(t_sys));
    if (!sys)
        system_exit(sys, E_ALLOCATE);
    memset(sys, 0, sizeof(t_sys));
    sys->number_of_philosophers = fetch_number(*++argv,sys);
    sys->time_to_die = fetch_number(*++argv,sys);
    sys->time_to_eat = fetch_number(*++argv,sys);
    sys->time_to_sleep = fetch_number(*++argv,sys);
    if (*++argv)
        sys->number_of_times_each_philosopher_must_eat = fetch_number(*argv,sys);
    give_birth(sys->number_of_philosophers,sys);
    return sys;
}