/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:00:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 16:18:27 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SLEEP_PING_MS 100
# define MS_FACTOR 1000

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
	pthread_t			thread;
	int					id;
	int					l_fork;
	int					r_fork;
	pthread_mutex_t		dying_time_lock; //for death_thread monitor
	long				next_dying_time;
	pthread_mutex_t		times_eaten_lock;
	int					times_eaten;
	struct s_context	*context;
}	t_philo;

typedef struct s_context
{
	pthread_t			death_thread;
	pthread_mutex_t		*fork_locks;
	int					*forks;
	int					n_philos;
	int					ms_ttd;
	int					ms_eat;
	int					ms_sleep;
	int					n_eats;
	long				start_ts;
	pthread_mutex_t		output_lock; //protect the stdout
	pthread_mutex_t		n_philos_that_ate_n_eats_lock; //for fifth param
	int					n_philos_that_ate_n_eats;	
	pthread_mutex_t		death_lock; //if someone starved 
	int					death;
}	t_context;

// async_handler.c
t_context	*init_context(int argc, char **argv);
t_philo		*create_philos(t_context *context);
void		clear_context(t_philo *philos, t_context *context);

//async.c
void		simulation(t_context *context, t_philo *philos);
void		*check_death(void *args);
int			check_finished(t_context *context);

// routine.c
void		*routine(void *arg);
void		handle_one_philo(t_context *context);

// parser.c
int			check_philo_input(int argc, char **argv);
int			ft_atoi(const char *nptr);

// utils.c
long		ft_gettime(void);
void		print_message(t_context *context, int id, enum e_state state, long time);
void		ft_usleep(int time, t_context *context);
void		*ft_calloc(size_t count, size_t size);

#endif
