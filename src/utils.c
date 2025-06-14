/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:43:36 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 14:47:16 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// if context != NULL, it stops microsleeping when someone is dead
void	ft_usleep(int time, t_context *context)
{
	long	start_time;

	start_time = ft_gettime();
	while (!check_finished(context) && ft_gettime() - start_time < time)
		usleep(SLEEP_PING_MS);
	return ;
}

long	ft_gettime(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * MS_FACTOR + time.tv_usec / MS_FACTOR;
	return (ms);
}

void	print_message(t_context *context, int id, enum e_state state)
{
	long	time;

	if (!context)
		return ;
	pthread_mutex_lock(&context->output_lock);
	if (!check_finished(context))
	{
		time = ft_gettime() - context->start_ts;
		if (state == FORK)
			printf("%ld %d has taken a fork\n", time, id);
		if (state == EAT)
			printf("%ld %d is eating\n", time, id);
		if (state == SLEEP)
			printf("%ld %d is sleeping\n", time, id);
		if (state == THINK)
			printf("%ld %d is thinking\n", time, id);
	}
	pthread_mutex_unlock(&context->output_lock);
}

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			tam;
	unsigned char	*res;

	tam = size * count;
	res = malloc((int)tam);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, tam);
	return (res);
}