/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:59:48 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/29 03:29:26 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_join(t_philos *philo, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			return (1);
		(philo[i].r_fork);
	}
	(philo->printf_mutex);
	return (0);
}

int	thinking(t_philos *philo)
{
	if (*(philo->alive) == true)
		printer(philo, "is thinking\n", 0);
	if (philo->meal_eaten == 0)
	{
		if (ft_sleep(100, philo))
			return (1);
	}
	return (0);
}

int	eating(t_philos *ph)
{
	sem_wait(ph->l_fork);
	if (*(ph->alive) == true)
		printer(ph, "has taken a fork\n", 0);
	sem_wait(ph->r_fork);
	if (*(ph->alive) == true)
		printer(ph, "has taken a fork\n", 0);
	if (*(ph->alive) == true)
		printer(ph, "is eating\n", 0);
	ph->last_meal = ft_get_time() - ph->arg->time_stamp;
	if (ft_sleep(ph->arg->time_to_eat, ph))
	{
		sem_post(ph->r_fork);
		sem_post(ph->l_fork);
		return (1);
	}
	sem_post(ph->r_fork);
	sem_post(ph->l_fork);
	ph->meal_eaten++;
	return (0);
}

int	sleeping(t_philos *philo)
{
	if (*(philo->alive) == true)
		printer(philo, "is sleeping\n", 0);
	if (ft_sleep(philo->arg->time_to_sleep, philo))
		return (1);
	return (0);
}
