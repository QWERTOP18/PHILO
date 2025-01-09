/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:19:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/09 10:04:54 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_bonus.h"
#include "system_bonus.h"
#include "utils_bonus.h"

int		check_status(t_sys *sys);
int		check_is_satisfy(t_sys *sys);

void	*__daemon(void *void_sys)
{
	t_sys	*sys;

	sys = (t_sys *)void_sys;
	while (1)
	{
		if (check_is_satisfy(sys))
		{
			return (NULL);
		}
		if (check_status(sys))
		{
			sem_wait(sys->sem_log);
			printf(BG_WHITE);
			philo_log(sys->id + 1, "died" RESET, sys);
			exit(2);
		}
	}
	return (NULL);
}

int	check_is_satisfy(t_sys *sys)
{
	int	ret;

	sem_wait(sys->sem_log);
	ret = sys->number_of_times_to_eat >= sys->number_of_times_each_must_eat;
	sys->status = ret;
	sem_post(sys->sem_log);
	return (ret);
}

/* I should handle status but sem_unlink during sem_wait says no error :) */
int	check_status(t_sys *sys)
{
	long long	elapsed_time;
	int			ret;

	sem_wait(sys->sem_log);
	elapsed_time = fetch_time() - sys->last_meal_time;
	ret = elapsed_time >= sys->time_to_die;
	sem_post(sys->sem_log);
	return (ret);
}
