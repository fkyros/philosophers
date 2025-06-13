/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/13 17:50:03 by gade-oli         ###   ########.fr       */
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

static void	ft_eat(t_philo *philo, t_context *context)
{
	long	time;
	int	first_fork;
	int	second_fork;

	// Ensure ordered locking -> TODO: creo que sobra
	first_fork = philo->l_fork;
	second_fork = philo->r_fork;
	if (first_fork > second_fork)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}

	time = ft_gettime() - context->start_ts;
	pthread_mutex_lock(&context->fork_locks[philo->l_fork]);
	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, FORK, time);
	pthread_mutex_lock(&context->fork_locks[philo->r_fork]);
	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, FORK, time);
	time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, EAT, time);
	pthread_mutex_lock(&context->n_eats_lock);
	ft_usleep(philo->context->ms_eat);
	context->n_eats++;
	pthread_mutex_unlock(&context->n_eats_lock);
	philo->last_meal_ts = ft_gettime() - context->start_ts;
	pthread_mutex_unlock(&context->fork_locks[philo->l_fork]);
	pthread_mutex_unlock(&context->fork_locks[philo->r_fork]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(50);
	while (1) //TODO: check if dead
	{
		ft_think(philo, philo->context);
		ft_eat(philo, philo->context);
		ft_sleep(philo, philo->context);
	}
	return (NULL);
}
