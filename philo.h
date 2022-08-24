/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:05:44 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/24 20:17:56 by yjarhbou         ###   ########.fr       */
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
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*printf_mutex;
	long				last_meal;
	int					meal_eaten;
	bool				*alive;
}	t_philos;

int	check_argment(int ac, char **av);
int	ft_atoi(const char *str);
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
