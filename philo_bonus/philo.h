/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:05:44 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/29 03:14:43 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdlib.h"
# include "pthread.h"
# include "time.h"
# include "sys/time.h"
# include <stdbool.h>
# include "stdio.h"
# include "semaphore.h"

typedef struct s_argument
{
	long	time_stamp;
	int		philo_nbr;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		number_meal;
}	t_myargument;

typedef struct s_philo
{
	int					id;
	pthread_t			philo_thread;
	t_myargument		*arg;
	sem_t				*r_fork;
	sem_t				*l_fork;
	sem_t				*printf_mutex;
	long				last_meal;
	int					meal_eaten;
	bool				*alive;
}	t_philos;

int	ft_atoi(const char *str);
int	check_argment(int ac, char **av);
long	ft_get_time(void);
void	init_stack(t_myargument *arg, char **av, int ac);
int		init_helper(t_philos *philo, t_myargument *arg);
t_philos	*init_struct(t_myargument *arg);
int	ft_pthread_join(t_philos *philo, int nbr);
int	thinking(t_philos *philo);
int	eating(t_philos *ph);
int	sleeping(t_philos *philo);
void	*actions(void *ph);
int	printer(t_philos *philo, char *msg, int dead);
int	free_data(t_philos *ph);
int	ft_sleep(long s_time, t_philos *philo);

#endif



	// t_philo	*philo;

	// philo = (t_philo *)malloc(sizeof(t_philo) * param->philos_nbr);
	// philo->alive = (bool *)malloc(sizeof(bool));
	// philo->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// if (!philo || !philo->alive || !philo->print)
	// 	return (NULL);
	// *(philo->alive) = true;
	// if (pthread_mutex_init(philo->print, NULL))
	// 	return (NULL);
	// if (fill_philo(philo, param))
	// 	return (NULL);
	// return (philo);