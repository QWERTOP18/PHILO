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

void philo_init(int num, t_sys *sys)
{
    sys->philos = malloc(sizeof(t_philo *) * (num+1));
    t_philo *philo;
    memset(sys->philos, 0, sizeof(t_philo *) * (num+1));
    int i;
    i = 0;
    while (i < num)
    {
        
        philo = (t_philo *)malloc(sizeof(t_philo));
        if (!sys->philos[i])
            system_exit(sys, 1);
        philo->id = i;
        philo->last_meal_time = sys->start_time;
        philo->number_of_times_to_eat = 0;
        pthread_mutex_init(&philo->fork,NULL);
        sys->philos[i++] = philo;
    }
}

t_sys *system_init(int argc, char **argv)
{
    t_sys *sys;

    sys = NULL;

    sys = (t_sys *)malloc(sizeof(t_sys));
    if (!sys)
        system_exit(sys, E_ALLOCATE);
    memset(sys, 0, sizeof(t_sys));
    sys->number_of_philosophers = fetch_number(*++argv,sys);
    if (sys->number_of_philosophers == 0)
        system_exit(sys, E_ALLOCATE);
    sys->time_to_die = fetch_number(*++argv,sys);
    sys->time_to_eat = fetch_number(*++argv,sys);
    sys->time_to_sleep = fetch_number(*++argv,sys);
    if (*++argv)
        sys->number_of_times_each_philosopher_must_eat = fetch_number(*argv,sys);
    philo_init(sys->number_of_philosophers,sys);
    return sys;
}