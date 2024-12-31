#include "system_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"



int check_is_dead(t_sys *sys);
int check_is_satisfy(t_sys *sys);


void   *__daemon(void *void_sys)
{
    t_sys *sys = (t_sys *)void_sys;
    while (1)
    {
        if (check_is_satisfy(sys))
            exit(0);
        if (check_is_dead(sys))
            exit(1);
    }
    return NULL;
}


int check_is_satisfy(t_sys *sys)
{
    return (sys->number_of_times_to_eat >= sys->number_of_times_each_philosopher_must_eat);
}

int check_is_dead(t_sys *sys)
{
    long long elapsed_time;

    elapsed_time = fetch_time() - sys->last_meal_time;
    return (elapsed_time >= sys->time_to_die);
}

