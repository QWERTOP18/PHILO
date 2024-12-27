#include "system.h"
#include <string.h>



void system_exit(t_sys *sys, int status)
{

    exit(status);
}

void give_birth(t_sys *sys)
{
    sys->philos = malloc(sizeof(t_philo *) * (sys->number_of_philosophers+1));
    memset(sys->philos, 0, sizeof(t_philo *) * (sys->number_of_philosophers+1));
    int i;
    i = 0;
    while (i < sys->number_of_philosophers)
    {
        sys->philos[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!sys->philos[i])
            system_exit(sys, 1);
        sys->philos[i]->id = i;
        sys->philos[i]->last_meal_time = (long long *)malloc(sizeof(long long));
        sys->philos[i]->last_meal_time = sys->born_time;
        sys->philos[i]->number_of_times_to_eat = 0;
        sys->philos[i]->is_dead = 0;
        sys->philos[i]->forks = (i + 1) % sys->number_of_philosophers;
    }


}

t_sys *system_init(int argc, char **argv)
{
    t_sys *sys;

    if (argc < 6)
        return NULL;
    sys = (t_sys *)malloc(sizeof(t_sys));
    if (!sys)
        return NULL;
    memset(sys, 0, sizeof(t_sys));
    sys->number_of_philosophers = ft_atoi(*++argv);
    sys->time_to_die = ft_atoi(*++argv);
    sys->time_to_eat = ft_atoi(*++argv);
    sys->time_to_sleep = ft_atoi(*++argv);
    if (*++argv)
        sys->number_of_times_each_philosopher_must_eat = ft_atoi(*argv);
    give_birth(sys);
    return sys;
}