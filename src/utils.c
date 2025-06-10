/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:43:36 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/07 13:55:25 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	ft_gettime(t_context *context)
{
	struct timeval	time;
	int		res;
	long		ms;

	res = gettimeofday(&time, NULL);
	if (res == -1)
		return (-1);
	if (!context)
		return (time.tv_sec * 1000);
	ms = (time.tv_sec - context->start) * 1000;
	return (ms);
}
