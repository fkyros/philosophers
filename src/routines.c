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

static void	ft_think(t_philo *philo, t_context *context)
{
	print_message(context, philo->id, THINK);
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

// Even philosophers: right fork first
// Odd philosophers: left fork first
static void	ft_eat(t_philo *philo, t_context *context)
{
	int		first_fork;
	int		second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
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
	//if (philo->id % 2 == 1)
	//	ft_usleep(philo->context->ms_eat / 2, NULL);
	while (!check_finished(philo->context))
	{
		ft_think(philo, philo->context);
		if (philo->id % 2 == 1 &&
				ft_gettime() < philo->context->start_ts + (philo->context->ms_eat / philo->context->n_philos))
			ft_usleep((philo->context->ms_eat / 2), NULL);
		ft_eat(philo, philo->context);
		ft_sleep(philo, philo->context);
	}
	return (NULL);
}

// to avoid a dead lock with the death_thread, for a single philo 
// we have to simulate its simulation 
void	handle_one_philo(t_context *context)
{
	print_message(context, 1, THINK);
	print_message(context, 1, FORK);
	ft_usleep(context->ms_ttd, NULL);
	print_message(context, 1, DEAD);
}
