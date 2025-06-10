/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/10 19:34:29 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_context	*context;
	//t_philo		*philos;

	context = (t_context *)arg;
	//philos = context->philos;
	//ft_eat(context);
	//ft_sleep();
	//ft_think();
	return (context);
}

void	print_message(t_context *context, int id, enum e_state state, long time)
{
	if (!context)
		return ;
	pthread_mutex_lock(&context->output);
	if (state == FORK)
		printf("%ld %d has taken a fork\n", time, id);
	if (state == EAT)
		printf("%ld %d is eating\n", time, id);
	if (state == SLEEP)
		printf("%ld %d is sleeping\n", time, id);
	if (state == THINK)
		printf("%ld %d is thinking\n", time, id);
	if (state == DEAD)
		printf("%ld %d died\n", time, id);
	pthread_mutex_unlock(&context->output);
}
