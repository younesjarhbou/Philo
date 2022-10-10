/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:59:48 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/10 07:47:57 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_pthread_join(t_philos *philo, int nbr)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < nbr)
// 		pthread_mutex_destroy(philo[i].r_fork);
// 	if (pthread_mutex_destroy(philo->printf_mutex) != 0)
// 	{
// 		sem_post(philo->printf_mutex);
// 		pthread_mutex_destroy(philo->printf_mutex);
// 	}
// 	return (0);
// }

int	eating(t_philos *ph)
{
	sem_wait(ph->r_fork);
	printer(ph, "has taken a fork\n");
	sem_wait(ph->r_fork);
	printer(ph, "has taken a fork\n");
	printer(ph, "is eating\n");
	ph->last_meal = ft_time(ph);
	ph->meal_eaten++;
	ft_sleep(ph->arg->time_to_eat);
	sem_post(ph->r_fork);
	sem_post(ph->r_fork);
	return (0);
}

int	sleeping(t_philos *philo)
{
	printer(philo, "is sleeping\n");
	if (ft_sleep(philo->arg->time_to_sleep))
		return (1);
	return (0);
}

int	ft_time(t_philos *ph)
{
	return (ft_get_time() - ph->arg->time_stamp);
}
