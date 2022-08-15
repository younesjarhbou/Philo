/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:16:11 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/15 23:36:52 by yjarhbou         ###   ########.fr       */
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

	i = 0;
	if (ac != 5 && ac != 6)
		ft_exit("Error\n syntax error too many | less argument", 1);
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
}

int	init_helper(t_philos *philo, t_myargument arg)
{
	int	i;

	i = -1;
	while (++i < arg.philo_nbr)
	{
		philo[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&philo[i].r_fork, NULL) || !philo[i].r_fork)
			ft_exit("Error\n Allocation faild", 1);
	}
	i = -1;
	while (++i < arg.philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].meal_eaten = 0;
		philo[i].alive = philo[0].alive;
		philo[i].arg = arg;
		philo[i].id = i + 1;
		philo[i].l_fork = philo[(i + 1) % arg.philo_nbr].r_fork;
		if (pthread_create(&philo.philo_thread, NULL, &fthread, NULL))
			return (1);
	}
	return (0);
}

t_philos	*init_struct(t_myargument arg)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos) * arg.philo_nbr);
	philo[0].alive = malloc(sizeof(bool));
	philo[0].printf = malloc(sizeof(pthread_mutex_t));
	if (!philo || !philo.alive || !philo.printf
		|| pthread_mutex_init(&philo[0].printf, NULL))
		return (NULL);
	if (init_helper(&philo, arg))
		return (NULL);
	return (philo);
}

int	pthread_join(t_philos philo)
{
	int	i;

	i = -1;
	while (++i < philo.arg.philo_nbr)
	{
		if (pthread_join(philo[i].philo_thread, NULL)
			|| pthread_mutex_destroy(philo[i].r_fork))
			return (1);
	}
	if (pthread_mutex_destroy(philo.printf_mutex))
		return (1);
	return (0);
}

int	printer(t_philos philo, char *msg, int dead)
{
	if (philo.alive == true)
	{
		if (pthread_mutex_lock(&(philo.printf_mutex)))
			return (1);
		printf("%ld philo %d", ft_get_time() - philo.arg.time_stamp, &philo.id);
		if (dead)
			philo.alive = false;
		printf("%s", &msg);
		if (pthread_mutex_unlock(&(philo.printf_mutex)))
			return (1);
	}
	return (0);
}

void	ft_exit(char *msg, int x)
{
	printf("Error\n %s", &msg);
}

int	main(int ac, char **av)
{
	t_myargument	arg;
	t_philos		*philos;

	check_argment(ac, av);
	philo = init_stack(&arg, av);

    return (0);
}