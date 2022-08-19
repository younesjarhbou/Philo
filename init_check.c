/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:57:26 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/19 01:54:31 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (str[i] == '-')
		printf("Error\n negative number detected");
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		else
			exit(1);
	}
	return ((int) nbr);
}

int	check_argment(int ac)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("Error\n syntax error too many | less argument"), 0);
	return (1);
}

long	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

void	init_stack(t_myargument *arg, char **av)
{
	arg->time_stamp = ft_get_time();
	arg->philo_nbr = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ft_atoi(av[5]))
		arg->number_meal = ft_atoi(av[5]);
	else
		arg->number_meal = -1;
}

int	init_helper(t_philos *ph, t_myargument *arg)
{
	int	i;

	i = 0;
	while (i < arg->philo_nbr)
	{
		ph[i].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!ph[i].r_fork || pthread_mutex_init(ph[i].r_fork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < arg->philo_nbr)
	{
		ph[i].id = i + 1;
		ph[i].l_fork = ph[(i + 1) % arg->philo_nbr].r_fork;
		ph[i].alive = ph[0].alive;
		ph[i].printf_mutex = ph[0].printf_mutex;
		ph[i].arg = arg;
		ph[i].last_meal = 0;
		ph[i].meal_eaten = 0;
		if (pthread_create(&ph[i].philo_thread, 0, &actions, (void *)&ph[i]))
			return (1);
		i++;
	}
	return (0);
}