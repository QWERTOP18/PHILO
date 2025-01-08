/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:40:02 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/08 19:57:39 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "system.h"
# include "unistd.h"
# include <sys/time.h>

int			fetch_number(const char *str, t_sys *sys);

long long	fetch_time(void);

void		well_sleep(int time);

int			philo_log(int id, const char *msg, t_sys *sys);

#endif