/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:16:11 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/21 01:51:07 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*init_struct(t_myargument *arg)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos) * arg->philo_nbr);
	philo->alive = (bool *)malloc(sizeof(bool));
	*(philo->alive) = true;
	philo->printf_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo || !philo->alive || !philo->printf_mutex
		|| pthread_mutex_init(philo->printf_mutex, NULL))
		return (NULL);
	if (init_helper(philo, arg))
		return (NULL);
	return (philo);
}

void	*actions(void *ph)
{
	t_philos		*philo;

	philo = (t_philos *)ph;
	if (philo == NULL || philo->arg->philo_nbr == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		thinking(philo);
	while (1)
	{
		if (eating(philo))
			break ;
		if (philo->meal_eaten == philo->arg->number_meal)
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_myargument	arg;
	t_philos		*philo;

	if (!check_argment(ac))
		return (1);
	init_stack(&arg, av, ac);
	philo = init_struct(&arg);
	if (philo == NULL && free_data(philo) == 0)
		return (1);
	if (arg.philo_nbr == 1)
	{
		printer(philo, "has taken a fork\n", 0);
		ft_sleep(arg.time_to_die, philo);
		printer(philo, "died\n", 1);
	}
	if (ft_pthread_join(philo, arg.philo_nbr) && free_data(philo) == 0)
		return (1);
	free_data(philo);
	return (0);
}
