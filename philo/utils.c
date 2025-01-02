#include "utils.h"
#include <limits.h>

int	fetch_number(const char *str, t_sys *sys)
{
    int        i;
    long long    result;

    i = 0;
    result = 0;
    while (str[i] == ' ' ||( str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
        system_exit(sys, E_ARGS);
    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i++] - '0');
        if (result > INT_MAX)
            system_exit(sys, E_ARGS);
    }
    if (str[i] != '\0')
      system_exit(sys, E_ARGS);
    return (int)result;
}


long long	fetch_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    philo_log(int id, const char *msg, t_sys *sys)
{
    long long    time;

    time = fetch_time() - sys->start_time;
    printf("%lld %d %s\n", time, id, msg);
}

void well_sleep(int time)
{
    long long    start_time;

    start_time = fetch_time();
    while (fetch_time() - start_time < time)
        usleep(50);
}