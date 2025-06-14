/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 17:56:19 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	ft_sleep(t_philo *philo, t_context *context)
{
	print_message(context, philo->id, SLEEP);
	ft_usleep(context->ms_sleep, context);
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

// even philosophers: right fork first
// odd philosophers: left fork first
static void	choose_fork(t_philo *philo, int *first, int *second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
	else
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
}

static void	ft_eat(t_philo *philo, t_context *context)
{
	int		first_fork;
	int		second_fork;

	choose_fork(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&context->fork_locks[first_fork]);
	context->forks[first_fork] = 1;
	print_message(context, philo->id, FORK);
	pthread_mutex_lock(&context->fork_locks[second_fork]);
	print_message(context, philo->id, FORK);
	context->forks[second_fork] = 1;
	pthread_mutex_lock(&philo->dying_time_lock);
	philo->next_dying_time = ft_gettime() + philo->context->ms_ttd;
	pthread_mutex_unlock(&philo->dying_time_lock);
	print_message(context, philo->id, EAT);
	ft_usleep(philo->context->ms_eat, context);
	context->forks[first_fork] = 0;
	context->forks[second_fork] = 0;
	pthread_mutex_unlock(&context->fork_locks[second_fork]);
	pthread_mutex_unlock(&context->fork_locks[first_fork]);
	check_finished_eating(context, philo);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!check_finished(philo->context))
	{
		print_message(philo->context, philo->id, THINK);
		if (philo->id % 2 == 1
			&& ft_gettime() < philo->context->start_ts
			+ (philo->context->ms_eat / philo->context->n_philos))
			ft_usleep(20, NULL);
		ft_eat(philo, philo->context);
		ft_sleep(philo, philo->context);
	}
	return (NULL);
}
