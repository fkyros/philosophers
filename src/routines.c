/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 16:18:22 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	ft_sleep(t_philo *philo, t_context *context)
{
	long	time;

	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, SLEEP, time);
	ft_usleep(context->ms_sleep);
}

static void	ft_think(t_philo *philo, t_context *context)
{
	long	time;

	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, THINK, time);
}

static void	check_finished_eating(t_context *context, t_philo *philo)
{
	pthread_mutex_lock(&philo->times_eaten_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_lock);
	if (context->n_eats != -1 && philo->times_eaten == context->n_eats)
	{
		pthread_mutex_lock(&context->n_philos_that_ate_n_eats_lock);
		context->n_philos_that_ate_n_eats++;
		pthread_mutex_unlock(&context->n_philos_that_ate_n_eats_lock);
	}
}

static void	ft_eat(t_philo *philo, t_context *context)
{
	long	time;

	pthread_mutex_lock(&context->fork_locks[philo->l_fork]);
	time = ft_gettime() - context->start_ts;
	context->forks[philo->l_fork] = 1;
	print_message(context, philo->id, FORK, time);
	pthread_mutex_lock(&context->fork_locks[philo->r_fork]);
	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, FORK, time);
	context->forks[philo->r_fork] = 1;
	pthread_mutex_lock(&philo->dying_time_lock);
	philo->next_dying_time = ft_gettime() + philo->context->ms_ttd;
	pthread_mutex_unlock(&philo->dying_time_lock);
	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, EAT, time);
	ft_usleep(philo->context->ms_eat);
	context->forks[philo->l_fork] = 0;
	context->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&context->fork_locks[philo->l_fork]);
	pthread_mutex_unlock(&context->fork_locks[philo->r_fork]);
	check_finished_eating(context, philo);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(50);
	while (!check_finished(philo->context))
	{
		ft_think(philo, philo->context);
		ft_eat(philo, philo->context);
		ft_sleep(philo, philo->context);
	}
	return (NULL);
}

// to avoid a dead lock with the death_thread, for a single philo 
// we have to simulate its simulation 
void	handle_one_philo(t_context *context)
{
	long	time;

	time = ft_gettime() - context->start_ts;
	print_message(context, 0, THINK, time);
	time = ft_gettime() - context->start_ts;
	print_message(context, 0, FORK, time);
	ft_usleep(context->ms_ttd);
	time = ft_gettime() - context->start_ts;
	print_message(context, 0, DEAD, time);
}