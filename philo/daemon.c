#include "system.h"
#include "utils.h"
#include "color.h"



int check_is_dead(t_sys *sys);
int check_is_satisfy(t_sys *sys);


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


int check_is_satisfy(t_sys *sys)
{
    int i = 0;
    while (i < sys->number_of_philosophers)
    {
        pthread_mutex_lock(&sys->mutex_log);
        if (sys->philos[i].number_of_times_to_eat < sys->number_of_times_each_philosopher_must_eat)
        {
            pthread_mutex_unlock(&sys->mutex_log);
            return 0;
        }
        pthread_mutex_unlock(&sys->mutex_log);
        i++;
    }
    //pthread_mutex_lock(&sys->mutex_log);
    return 1;
}

int check_is_dead(t_sys *sys)
{
    int i = 0;
    long long elapsed_time;
    while (i < sys->number_of_philosophers)
    {
        pthread_mutex_lock(&sys->mutex_log);
        elapsed_time = fetch_time() - sys->philos[i].last_meal_time;
        if (elapsed_time >= sys->time_to_die)
        {
            printf(BG_RED);
            philo_log(i+1, "died", sys);
            printf(RESET);
            return 1;
        }
        pthread_mutex_unlock(&sys->mutex_log);
        i++;
    }
    return 0;
}

