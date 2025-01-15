/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/01/15 18:53:17 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "../megalibft/libft.h"

enum	e_state {EAT, SLEEP, THINK};

typedef	struct s_philo
{
	pthread_t		thread;
	int				state;
	pthread_mutex_t	mt;
	int				fork;
	int				ms_eat;
	int				ms_sleep;
	int				ms_think;
}	t_philo;

#endif
