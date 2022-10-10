/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:58:17 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/10 05:27:16 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_philos *ph, t_global *s_gl)
{
	free(s_gl->philo_pid);
	free(ph);
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	return (0);
}

int	ft_sleep(long s_time)
{
	long	sleep_start;
	long	current_time;

	sleep_start = ft_get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		usleep(150);
		current_time = ft_get_time();
	}
	return (0);
}

int	printer(t_philos *ph, char *msg)
{
	sem_wait(ph->printf_mutex);
	printf("%ld philo %d ", ft_get_time() - ph->arg->time_stamp, ph->id);
	printf("%s", msg);
	sem_post(ph->printf_mutex);
	return (0);
}

int	printer_last(t_philos *ph, char *msg)
{
	sem_wait(ph->printf_mutex);
	printf("%ld philo %d ", ft_get_time() - ph->arg->time_stamp, ph->id);
	printf("%s", msg);
	return (0);
}
