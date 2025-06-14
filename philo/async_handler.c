/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:44:40 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 22:44:42 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutex_and_forks(t_context *context)
{
	int	i;
	int	n;

	i = 0;
	n = context->n_philos;
	context->fork_locks = malloc(sizeof(pthread_mutex_t) * n);
	if (!context->fork_locks)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return ;
	}
	context->forks = ft_calloc(context->n_philos, sizeof(int));
	if (!context->forks)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return ;
	}
	while (i < n)
	{
		pthread_mutex_init(&context->fork_locks[i], NULL);
		i++;
	}
	pthread_mutex_init(&context->output_lock, NULL);
	pthread_mutex_init(&context->death_lock, NULL);
	pthread_mutex_init(&context->n_philos_that_ate_n_eats_lock, NULL);
}

t_context	*init_context(int argc, char **argv)
{
	t_context	*context;

	context = malloc(sizeof(t_context));
	if (!context)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return (NULL);
	}
	context->n_philos = ft_atoi(argv[1]);
	context->ms_ttd = ft_atoi(argv[2]);
	context->ms_eat = ft_atoi(argv[3]);
	context->ms_sleep = ft_atoi(argv[4]);
	context->n_eats = -1;
	if (argc == 6)
		context->n_eats = ft_atoi(argv[5]);
	context->start_ts = ft_gettime();
	context->n_philos_that_ate_n_eats = 0;
	context->death = 0;
	init_mutex_and_forks(context);
	return (context);
}

t_philo	*create_philos(t_context *context)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * context->n_philos);
	if (!philos)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return (NULL);
	}
	while (i < context->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].l_fork = i;
		philos[i].r_fork = i + 1;
		if (i + 1 == context->n_philos)
			philos[i].r_fork = 0;
		philos[i].times_eaten = 0;
		pthread_mutex_init(&philos[i].times_eaten_lock, NULL);
		philos[i].next_dying_time = ft_gettime() + context->ms_ttd;
		pthread_mutex_init(&philos[i].dying_time_lock, NULL);
		philos[i].context = context;
		i++;
	}
	return (philos);
}

void	clear_context(t_philo *philos, t_context *context)
{
	int	i;

	i = 0;
	pthread_join(context->death_thread, NULL);
	while (i < context->n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < context->n_philos)
	{
		pthread_mutex_destroy(&context->fork_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&context->n_philos_that_ate_n_eats_lock);
	pthread_mutex_destroy(&context->death_lock);
	pthread_mutex_destroy(&context->output_lock);
	free(context->fork_locks);
	free(context->forks);
	free(philos);
	free(context);
}

// to avoid a dead lock with the death_thread, for a single philo 
// we have to simulate its simulation 
void	handle_one_philo(t_context *context)
{
	long	time;

	print_message(context, 1, THINK);
	print_message(context, 1, FORK);
	ft_usleep(context->ms_ttd, NULL);
	time = ft_gettime() - context->start_ts;
	printf("%ld %d died\n", time, 1);
}
