/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:58:17 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/21 01:55:21 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int	free_data(t_philos *ph)
{
	int	i;
	int	philo_nbr;

	i = 0;
	philo_nbr = ph->arg->philo_nbr;
	while (i < philo_nbr)
	{
		if (ph[i].r_fork != NULL)
			free(ph[i].r_fork);
		i++;
	}
	if (ph->alive != NULL)
		free(ph->alive);
	if (ph->printf_mutex != NULL)
		free(ph->printf_mutex);
	if (ph != NULL)
		free(ph);
	return (0);
}

int	ft_sleep(long s_time, t_philos *ph)
{
	long	sleep_start;
	long	current_time;

	sleep_start = get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		if (*(ph->alive) == false)
		{
			usleep(150);
			return (1);
		}
		if (ph->arg->time_to_die < ((current_time - ph->arg->time_stamp) \
					- ph->last_meal))
		{
			printer(ph, "died\n", 1);
			return (1);
		}
		usleep(150);
		current_time = get_time();
	}
	return (0);
}

int	printer(t_philos *ph, char *msg, int dead)
{
	pthread_mutex_lock(ph->printf_mutex);
	if (ph->alive)
	{
		printf("%ld philo %d ", ft_get_time() - ph->arg->time_stamp, ph->id);
		if (dead == 1)
			ph->alive = false;
		printf("%s", msg);
		
	}
	pthread_mutex_unlock(ph->printf_mutex);
	return (0);
}