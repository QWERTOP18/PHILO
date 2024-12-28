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
