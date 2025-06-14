/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:27:34 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 18:08:34 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// creates the philosophers and death monitor threads
void	simulation(t_context *context, t_philo *philos)
{
	int	i;

	context->start_ts = ft_gettime();
	if (context->n_philos == 1)
	{
		handle_one_philo(context);
		return ;
	}
	pthread_create(&context->death_thread, NULL, &check_death, philos);
	i = 0;
	while (i < context->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}

static void	warn_end_simulation(t_philo philo)
{
	long	time;

	time = ft_gettime() - philo.context->start_ts;
	pthread_mutex_lock(&philo.context->output_lock);
	pthread_mutex_lock(&philo.context->death_lock);
	philo.context->death = 1;
	printf("%ld %d died\n", time, philo.id);
	pthread_mutex_unlock(&philo.context->death_lock);
	pthread_mutex_unlock(&philo.context->output_lock);
}

void	*check_death(void *args)
{
	int			i;
	t_context	*context;
	t_philo		*philos;

	philos = (t_philo *)args;
	context = philos[0].context;
	while (!check_finished(context))
	{
		i = 0;
		while (i < context->n_philos)
		{
			pthread_mutex_lock(&philos[i].dying_time_lock);
			if (ft_gettime() > philos[i].next_dying_time)
			{
				pthread_mutex_unlock(&philos[i].dying_time_lock);
				warn_end_simulation(philos[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].dying_time_lock);
			i++;
		}
	}
	return (NULL);
}

int	check_finished(t_context *context)
{
	int	stop_flag;

	stop_flag = 0;
	if (!context)
		return (0);
	pthread_mutex_lock(&context->death_lock);
	pthread_mutex_lock(&context->n_philos_that_ate_n_eats_lock);
	if (context->death
		|| context->n_philos_that_ate_n_eats == context->n_philos)
		stop_flag = 1;
	pthread_mutex_unlock(&context->n_philos_that_ate_n_eats_lock);
	pthread_mutex_unlock(&context->death_lock);
	return (stop_flag);
}
