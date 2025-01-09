/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:39:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 10:41:10 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "utils.h"
#include <limits.h>

int	fetch_number(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > INT_MAX)
			return (printf(RED "invalid input" RESET "\n"), -1);
	}
	if (str[i] != '\0')
		return (printf(RED "invalid input" RESET "\n"), -1);
	return ((int)result);
}

long long	fetch_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	philo_log(int id, const char *msg, t_sys *sys)
{
	long long	time;

	if (sys->is_sim_end)
		return (1);
	time = fetch_time() - sys->start_time;
	printf("%lld %d %s\n", time, id, msg);
	return (0);
}

void	well_sleep(int time)
{
	long long	start_time;

	start_time = fetch_time();
	while (fetch_time() - start_time < time)
		usleep(20);
}

int	validate(t_sys *sys)
{
	if (sys->number_of_philosophers <= 0 || sys->time_to_die <= 0
		|| sys->time_to_eat <= 0 || sys->time_to_sleep <= 0
		|| sys->number_of_times_each_must_eat <= 0)
		return (0);
	return (1);
}
