/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:16:11 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/10 18:55:36 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// sem_unlink("forks_sem");
// 	sem_unlink("print_sem");
// 	sem_unlink("done_sem");
// 	sem_unlink("finish_eat_sem");
// 	data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->nbr_of_philos);
// 	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
// 	data->done_sem = sem_open("done_sem", O_CREAT, 0644, 0);
// 	data->finish_eat_sem = sem_open("finish_eat_sem", O_CREAT, 0644, 0);
// 	if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED
// 		|| data->done_sem == SEM_FAILED || data->finish_eat_sem == SEM_FAILED)
// 		exit(EXIT_FAILURE);
t_philos	*init_struct(t_myargument *arg, t_global *s_global)
{
	t_philos	*philo;

	//sem_unlink("print_sem");
	philo = malloc(sizeof(t_philos) * arg->philo_nbr);
	//philo->printf_mutex = sem_open("print_sem", 0644, 1);
	// if (philo->printf_mutex == SEM_FAILED)
	// 	return (NULL);
	if (!philo)
		return (NULL);
	if (init_helper(philo, arg))
		return (NULL);
	if (init_global(philo, s_global))
		return (NULL);
	return (philo);
}

int	init_global(t_philos *ph, t_global *s_gl)
{
	int	i;
	int	pid;

	i = -1;
	s_gl->g_philo = ph;
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	sem_unlink("meal_sem");
	s_gl->meal_sem = (sem_t *)sem_open("meal_sem",
			O_CREAT, 0644, 0);
	s_gl->printf_mutex = (sem_t *) sem_open("print_sem", O_CREAT, 0644, 1);
	s_gl->r_fork = (sem_t *)sem_open("fork_sem", O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, ph->arg->philo_nbr);
	if (s_gl->printf_mutex == SEM_FAILED || s_gl->r_fork == SEM_FAILED
		|| s_gl->meal_sem == SEM_FAILED)
		return (1);
	s_gl->philo_pid = malloc (sizeof(int) * ph->arg->philo_nbr);
	if (!s_gl->philo_pid)
		return (free_data(ph, s_gl), exit(1), 1);
	while (++i < ph->arg->philo_nbr)
	{
		ph[i].r_fork = s_gl->r_fork;
		ph[i].printf_mutex = s_gl->printf_mutex;
		ph[i].meal_sem = s_gl->meal_sem;
		pid = fork();
		if (pid == 0)
			actions(ph + i);
		s_gl->philo_pid[i] = pid;
	}
	pthread_t checkmeal;
	pthread_create(&checkmeal, NULL, &ft_check_meals, (void *)s_gl);
	pthread_detach(checkmeal);
	return (0);
}

void	*actions(void *ph)
{
	t_philos		*philo;

	philo = (t_philos *)ph;
	if (pthread_create(&philo->check_done, 0, &ft_check_death, philo))
		return (0);
	pthread_detach(philo->check_done);
	if (philo == NULL)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_sleep(100);
	while (1)
	{
		printer(philo, "is thinking\n");
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*ft_check_meals(void *data)
{
	int			i;
	t_global	*s_gl;

	s_gl = (t_global *) data;
	i = -1;
	while (++i < s_gl->g_philo->arg->philo_nbr)
		sem_wait(s_gl->meal_sem);
	ft_kill_all(*s_gl);
	free_data(s_gl->g_philo, s_gl);
	exit(0);
	return (0);
}

void	*ft_check_death(void *ph)
{
	int			i;
	int			nbr;
	int			b;
	t_philos	*philo;

	b = 0;
	nbr = 0;
	i = -1;
	philo = (t_philos *)ph;
	while (1)
	{
		//printf("philo id = %d meal eaten = %d arg meal =%d time to die = %d\n", philo->id, philo->meal_eaten, philo->arg->number_meal,philo->arg->time_to_die);
		if ((ft_time(philo) - philo->last_meal) > philo->arg->time_to_die)
		{
			printer(philo, "died\n");
			sem_wait(philo->printf_mutex);
			exit(1);
		}
		// printf("philo id = %d meal eaten = %d arg meal =%d time to die = %d semwait = %d\n", 
		// philo->id, philo->meal_eaten, philo->arg->number_meal,philo->arg->time_to_die,(int) philo->meal_sem);
		if ( philo->arg->number_meal > 0 && philo->meal_eaten >= philo->arg->number_meal && b == 0)
		{
			//printf("hello there we are here %d %d %d\n", philo->id, philo->meal_eaten, philo->arg->number_meal);
			sem_post(philo->meal_sem);
			b = 1;
		}
		usleep(100);
	}
	return (0);
}

void	ft_kill_all(t_global s_gl)
{
	int	i;

	i = -1;
	while (++i < s_gl.g_philo->arg->philo_nbr)
		kill(s_gl.philo_pid[i], SIGKILL);
}

// syntax of waitpid():
// pid_t waitpid(pid_t pid, int *status, int options);
// The value of pid can be:
// < -1: Wait for any child process whose process group ID is equal to the absolute value of pid.
// -1: Wait for any child process.
// 0: Wait for any child process whose process group ID is equal to that of the calling process.
// > 0: Wait for the child whose process ID is equal to the value of pid.
// The value of options is an OR of zero or more of the following constants:
// WNOHANG: Return immediately if no child has exited.
// WUNTRACED: Also return if a child has stopped. Status for traced children which have stopped is provided even if this option is not specified.
// WCONTINUED: Also return if a stopped child has been resumed by delivery of SIGCONT.
int	main(int ac, char **av)
{
	t_myargument	arg;
	t_philos		*philo;
	t_global		s_gl;
	int				status;

	if (!check_argment(ac, av))
		return (1);
	init_stack(&arg, av, ac);
	philo = init_struct(&arg, &s_gl);
	if (philo == NULL)
		return (free_data(philo, &s_gl), 1);
	waitpid(-1, &status, 0);
	// if (!WIFEXITED(status))
	ft_kill_all(s_gl);
	free_data(philo, &s_gl);
	return (0);
}
