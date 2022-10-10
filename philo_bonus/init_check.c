/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:21:07 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/10 08:13:28 by yjarhbou         ###   ########.fr       */
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
	// sem_unlink("forks_sem");
	// sem_unlink("print_sem");
	// sem_unlink("done_sem");
	// sem_unlink("finish_eat_sem");
	// data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->nbr_of_philos);
	// data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	// data->done_sem = sem_open("done_sem", O_CREAT, 0644, 0);
	// data->finish_eat_sem = sem_open("finish_eat_sem", O_CREAT, 0644, 0);
	// if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED
	// 	|| data->done_sem == SEM_FAILED || data->finish_eat_sem == SEM_FAILED)
	// 	exit(EXIT_FAILURE);

int	init_helper(t_philos *ph, t_myargument *arg)
{
	int	i;

	i = -1;
	// while (++i < arg->philo_nbr)
	// {
	// 	ph[i].r_fork = sem_open("r_fork", O_CREAT, 0644, arg->philo_nbr);
	// 	if (ph->r_fork == SEM_FAILED)
	// 		return (1);
	// }
	i = -1;
	while (++i < arg->philo_nbr)
	{
		ph[i].id = i + 1;
	//	sem_unlink("printf_mutex");
		//ph[i].l_fork = ph[(i + 1) % arg->philo_nbr].r_fork;
	//	ph[i].printf_mutex = sem_open("printf_mutex", O_CREAT, 0644, 1);
		ph[i].arg = arg;
		ph[i].last_meal = ft_time(ph);
		ph[i].meal_eaten = 0;
		//ph[i].process_id = mall
		// if (pthread_create(&ph[i].philo_thread, 0, &actions, (void *)&ph[i]))
		// 	return (1);
		// pthread_detach(ph[i].philo_thread);
	}
	return (0);
}
