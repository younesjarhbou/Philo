/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:59:48 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/30 02:00:34 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_join(t_philos *philo, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		pthread_mutex_destroy(philo[i].r_fork);
	if (pthread_mutex_destroy(philo->printf_mutex) != 0)
	{
		pthread_mutex_unlock(philo->printf_mutex);
		pthread_mutex_destroy(philo->printf_mutex);
	}
	return (0);
}

int	eating(t_philos *ph)
{
	pthread_mutex_lock(ph->l_fork);
	printer(ph, "has taken a fork\n");
	pthread_mutex_lock(ph->r_fork);
	printer(ph, "has taken a fork\n");
	printer(ph, "is eating\n");
	ph->last_meal = ft_get_time() - ph->arg->time_stamp;
	if (ft_sleep(ph->arg->time_to_eat, ph))
	{
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		return (1);
	}
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	ph->meal_eaten++;
	return (0);
}

int	sleeping(t_philos *philo)
{
	printer(philo, "is sleeping\n");
	if (ft_sleep(philo->arg->time_to_sleep, philo))
		return (1);
	return (0);
}

int	ft_time(t_philos *ph)
{
	return (ft_get_time() - ph->arg->time_stamp);
}
