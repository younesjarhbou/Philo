/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:16:11 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/30 02:01:38 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*init_struct(t_myargument *arg)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos) * arg->philo_nbr);
	philo->printf_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo || !philo->printf_mutex
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
	if (philo->id % 2 == 0)
		ft_sleep(100, philo);
	while (1)
	{
		printer(philo, "is thinking\n");
		if (eating(philo))
			break ;
		if (philo->meal_eaten == philo->arg->number_meal)
			break ;
		if (sleeping(philo))
			break ;
	}
	return (NULL);
}

int	ft_check_meals(t_philos *philo)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = -1;
	while (++i < philo->arg->philo_nbr)
	{
		if (philo[i].meal_eaten >= philo[i].arg->number_meal)
			nbr++;
	}
	return (nbr == philo->arg->philo_nbr);
}

int	ft_check_death(t_philos *philo)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = -1;
	while (++i < philo->arg->philo_nbr)
	{
		if ((ft_time(philo) - philo[i].last_meal) > philo[i].arg->time_to_die)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_myargument	arg;
	t_philos		*philo;

	if (!check_argment(ac, av))
		return (1);
	init_stack(&arg, av, ac);
	philo = init_struct(&arg);
	if (philo == NULL && free_data(philo) == 0)
		return (1);
	while (1)
	{
		if (philo->arg->number_meal != -1 && ft_check_meals(philo) == 1)
			break ;
		if (ft_check_death(philo) == 1)
		{
			printer_last(philo, "died\n");
			break ;
		}
	}
	if (ft_pthread_join(philo, arg.philo_nbr) && free_data(philo) == 0)
		return (1);
	free_data(philo);
	return (0);
}
