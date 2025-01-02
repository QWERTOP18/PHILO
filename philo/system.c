#include "system.h"
#include "utils.h"
#include <string.h>
#include <limits.h>



void system_exit(t_sys *sys, int status)
{
    if (sys && sys->philos)
    {
        free(sys->philos);
    }
    free(sys);
    if(status)
        printf("Error\n");
    exit(status);
}


void system_wait(t_sys *sys)
{
    int i;
    i = 0;
    while (i < sys->number_of_philosophers)
    {
        usleep(100);
        pthread_mutex_destroy(&sys->philos[i].mutex_fork);
        pthread_detach(sys->philos[i].thread);
        i++;
    }    
    pthread_join(sys->daemon,NULL);
    pthread_mutex_destroy(&sys->mutex_log);
}

void philo_init(int num, t_sys *sys)
{
    sys->philos = malloc(sizeof(t_philo) * (num+1));
    if (!sys->philos)
        system_exit(sys, 1);
    memset(sys->philos, 0, sizeof(t_philo) * (num+1));
    int i;
    i = 0;
    while (i < num)
    {
        
        sys->philos[i].last_meal_time = sys->start_time;
        sys->philos[i].number_of_times_to_eat = 0;
        pthread_mutex_init(&sys->philos[i].mutex_fork,NULL);
        i++;
    }
}

t_sys *system_init(char **argv)
{
    t_sys *sys;

    sys = (t_sys *)malloc(sizeof(t_sys));
    if (!sys)
        system_exit(NULL, E_ALLOCATE);
    memset(sys, 0, sizeof(t_sys));
    sys->number_of_philosophers = fetch_number(*++argv,sys);
    if (sys->number_of_philosophers == 0)
        system_exit(sys, E_ALLOCATE);
    sys->time_to_die = fetch_number(*++argv,sys);
    sys->time_to_eat = fetch_number(*++argv,sys);
    sys->time_to_sleep = fetch_number(*++argv,sys);
    if (*++argv)
        sys->number_of_times_each_philosopher_must_eat = fetch_number(*argv,sys);
    else
        sys->number_of_times_each_philosopher_must_eat = INT_MAX;
    sys->start_time = fetch_time();
    philo_init(sys->number_of_philosophers,sys);
    pthread_mutex_init(&sys->mutex_log, NULL);

    return sys;
}