/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:43:36 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/13 17:28:37 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_usleep(int time)
{
	long	start_time;

	start_time = ft_gettime();
	while (ft_gettime() - start_time < time)
		usleep(500);
	return ;
}

long	ft_gettime(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	print_message(t_context *context, int id, enum e_state state, long time)
{
	if (!context)
		return ;
	pthread_mutex_lock(&context->output_lock);
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
	pthread_mutex_unlock(&context->output_lock);
}
