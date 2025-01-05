/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:53:19 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 20:00:25 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "system.h"
#include "utils.h"

int		check_is_dead(t_sys *sys);
int		check_is_satisfy(t_sys *sys);

void	*__daemon(void *void_sys)
{
	t_sys	*sys;

	sys = (t_sys *)void_sys;
	while (1)
	{
		if (check_is_satisfy(sys))
			return (NULL);
		if (check_is_dead(sys))
			return (NULL);
	}
}

int	check_is_satisfy(t_sys *sys)
{
	int	i;
	int	max_ct;

	i = 0;
	max_ct = sys->number_of_times_each_must_eat;
	while (i < sys->number_of_philosophers)
	{
		pthread_mutex_lock(&sys->mutex_log);
		if (sys->philos[i].number_of_times_to_eat < max_ct)
		{
			pthread_mutex_unlock(&sys->mutex_log);
			return (0);
		}
		pthread_mutex_unlock(&sys->mutex_log);
		i++;
	}
	return (1);
}
// pthread_mutex_lock(&sys->mutex_log);

int	check_is_dead(t_sys *sys)
{
	int			i;
	long long	elapsed_time;

	i = 0;
	while (i < sys->number_of_philosophers)
	{
		pthread_mutex_lock(&sys->mutex_log);
		elapsed_time = fetch_time() - sys->philos[i].last_meal_time;
		if (elapsed_time >= sys->time_to_die)
		{
			printf(BG_RED);
			philo_log(i + 1, "died" RESET, sys);
			return (1);
		}
		pthread_mutex_unlock(&sys->mutex_log);
		i++;
	}
	return (0);
}
