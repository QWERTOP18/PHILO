#ifndef UTILS_H
#define UTILS_H


#include "system.h"
#include <sys/time.h>
#include "unistd.h"
int	fetch_number(const char *str, t_sys *sys);

long long	fetch_time(void);

void well_sleep(int time);

void    philo_log(int id, const char *msg, t_sys *sys);

#endif