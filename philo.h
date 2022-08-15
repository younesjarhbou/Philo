/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:05:44 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/15 00:42:59 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdlib.h"
# include "pthread.h"
# include "time.h"
# include "sys/time.h"

# include "stdio.h"

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
	pthread				philo_thread;
	t_myargument		arg;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		printf_mutex;
	long				last_meal;
	int					meal_eaten;
	bool				alive;
}	t_philos;

#endif