/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/06 19:33:47 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

enum	e_state
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEAD
};

typedef	struct s_philo
{
	int		id;
	e_state		state;
	int		l_fork;
	int		r_fork;
}	t_philo;

typedef struct s_context
{
	int			n_philos;
	pthread_thread_t	*threads;
	pthread_mutex_t		*forks;
	t_philo			*philos;
	int			ms_total_die;
	int			ms_eat;
	int			ms_sleep;
	int			ms_think;
	int			n_intakes;
	pthread_mutex_t		*output; //protect the stdout
}	t_context;

int	ft_atoi(const char *nptr);

#endif
