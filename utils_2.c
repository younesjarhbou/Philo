/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:59:48 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/19 01:53:36 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_join(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philo->arg->philo_nbr)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			return (1);
		pthread_mutex_destroy(philo[i].r_fork);
	}
	pthread_mutex_destroy(philo->printf_mutex);
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
	pthread_mutex_lock(ph->l_fork);
	if (*(ph->alive) == true)
		printer(ph, "has taken a fork\n", 0);
	pthread_mutex_lock(ph->r_fork);
	if (*(ph->alive) == true)
		printer(ph, "has taken a fork\n", 0);
	if (*(ph->alive) == true)
		printer(ph, "is eating\n", 0);
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
	if (*(philo->alive) == true)
		printer(philo, "is sleeping\n", 0);
	if (ft_sleep(philo->arg->time_to_sleep, philo))
		return (1);
	return (0);
}

		// printf("has taken a fork\n");
		// else if (state == EATING)
		// 	printf("is eating\n");
		// else if (state == SLEEPING)
		// 	printf("is sleeping\n");
		// else if (state == THINKING)
		// 	printf("is thinking\n");
		// else if (state == DEAD)
		// {
		// 	printf("died\n");