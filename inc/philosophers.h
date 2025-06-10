/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/11 00:39:15 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum	e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef struct s_philo
{
	pthread_t		thread;
	enum e_state	state;
	int				id;
	pthread_mutex_t	*l_fork_lock; //all pointing to the real context source
	pthread_mutex_t	*r_fork_lock;
	int				l_fork;
	int				r_fork;
	long			last_meal_ts;
	struct s_context	*context;
}	t_philo;

typedef struct s_context
{
	pthread_mutex_t	*fork_locks;
	int				*forks;
	int				n_philos;
	int				ms_ttd;
	int				ms_eat;
	int				ms_sleep;
	int				ms_think;
	int				n_intakes;
	long			start_ts;
	pthread_mutex_t	output; //protect the stdout
	pthread_mutex_t	finish_lock;
	int				finish_flag; //for fifth param
	t_philo			*philos;
}	t_context;

// async.c
t_context	*init_context(int argc, char **argv);
void		create_philos(t_context *context);
void		simulation(t_philo *philos);
void		clear_context(t_context *context);

// routine.c
void	*routine(void *arg);

// parser.c
int	check_philo_input(int argc, char **argv);
int	ft_atoi(const char *nptr);

// utils.c
long	ft_gettime(void);
void	print_message(t_context *context, int id, enum e_state state, long time);

#endif
