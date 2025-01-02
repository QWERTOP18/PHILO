#include "system_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"



int check_is_dead(t_sys *sys);
int check_is_satisfy(t_sys *sys);


void   *__daemon(void *void_sys)
{
    t_sys *sys = (t_sys *)void_sys;
    if (check_is_satisfy(sys))
        exit(0);
    if (check_is_dead(sys))
    {
        sem_wait(sys->sem_log);
        printf(BG_MAGENTA);
        philo_log(sys->id+1,"died",sys);
        printf(RESET);
        exit(1);
    }
}


int check_is_satisfy(t_sys *sys)
{
    sem_wait(sys->sem_log);
    int ret = sys->number_of_times_to_eat >= sys->number_of_times_each_philosopher_must_eat;
    sem_post(sys->sem_log);
    return ret;
}

int check_is_dead(t_sys *sys)
{
    long long elapsed_time;
    sem_wait(sys->sem_log);
    elapsed_time = fetch_time() - sys->last_meal_time;
    int ret = elapsed_time >= sys->time_to_die;
    sem_post(sys->sem_log);
    return ret;
}

