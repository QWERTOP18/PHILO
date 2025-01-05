/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:24:59 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 19:41:56 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "system_bonus.h"
# include <sys/time.h>

int			fetch_number(const char *str, t_sys *sys);

long long	fetch_time(void);

void		well_sleep(int time);

void		philo_log(int id, const char *msg, t_sys *sys);

#endif