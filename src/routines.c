/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/10 21:47:05 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// TODO: context arriving as null??
static void    ft_sleep(t_philo *philo, t_context *context)
{
    long    time;

    time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, SLEEP, time);
}

static void    ft_think(t_philo *philo, t_context *context)
{
    long    time;

    time = ft_gettime() - context->start_ts;
	print_message(context, philo->id, THINK, time);
}

// TODO: include desync to make odd philos eat and not starve
void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		//ft_eat(context);
		ft_sleep(philo, philo->context);
		ft_think(philo, philo->context);
	}
	return (NULL);
}


