/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:21:07 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/30 01:56:23 by yjarhbou         ###   ########.fr       */
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

int	check_argment(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("Error\n syntax error too many | less argument"), 0);
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (printf("Error\n syntax"), 0);
		i++;
	}
	return (1);
}

long	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

void	init_stack(t_myargument *arg, char **av, int ac)
{
	arg->time_stamp = ft_get_time();
	arg->philo_nbr = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->number_meal = ft_atoi(av[5]);
	else
		arg->number_meal = -1;
}

int	init_helper(t_philos *ph, t_myargument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_nbr)
	{
		ph[i].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!ph[i].r_fork || pthread_mutex_init(ph[i].r_fork, NULL))
			return (1);
	}
	i = -1;
	while (++i < arg->philo_nbr)
	{
		ph[i].id = i + 1;
		ph[i].l_fork = ph[(i + 1) % arg->philo_nbr].r_fork;
		ph[i].printf_mutex = ph[0].printf_mutex;
		ph[i].arg = arg;
		ph[i].last_meal = ft_time(ph);
		ph[i].meal_eaten = 0;
		if (pthread_create(&ph[i].philo_thread, 0, &actions, (void *)&ph[i]))
			return (1);
		pthread_detach(ph[i].philo_thread);
	}
	return (0);
}
