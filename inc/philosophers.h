/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/10 21:40:35 by gade-oli         ###   ########.fr       */
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
	int				*l_fork;
	int				*r_fork;
}	t_philo;

typedef struct s_context
{
	t_philo			*philos;
	pthread_mutex_t	*fork_locks;
	int				*forks;
	int				n_philos;
	int				ms_total_die;
	int				ms_eat;
	int				ms_sleep;
	int				ms_think;
	int				n_intakes;
	long			start_ts;
	pthread_mutex_t	output; //protect the stdout
	pthread_mutex_t	finish_lock;
	int				finish_flag; //for fifth param
}	t_context;

// async.c
t_context	*init_context(int argc, char **argv);
void		clear_context(t_context *context);
void		launch_philos(t_context *context);
void		finish_philos(t_context *context);

// routine.c
void	*routine(void *arg);
void	print_message(t_context *context, int id, enum e_state state, long time);

// parser.c
int	check_philo_input(int argc, char **argv);
int	ft_atoi(const char *nptr);

// utils.c
long	ft_gettime(t_context *context);

#endif
