/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2024/12/19 16:58:34 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "../lib/megalibft/libft.h"

enum	e_state
{
	EAT,
	SLEEP,
	THINK
}

typedef	struct s_philo
{
	pthread_t		thread;
	e_state			state;
	pthread_mutex_t	mt;
	int				fork;
	int				ms_eat;
	int				ms_sleep;
	int				ms_think;
}	t_philo;

#endif
