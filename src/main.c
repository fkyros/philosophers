/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:21 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/06 19:33:37 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_philo	*init_philo(int ms_sleep, int ms_think, int ms_eat)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	p->state = SLEEP;
	p->ms_eat = ms_eat;
	p->ms_sleep = ms_sleep;
	p->ms_think = ms_think;
	return (p);
}

t_context	*init_context(int argc, char **argv)
{
	t_context	*context;

	context = malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->n_philos = ft_atoi(argv[1]);
	context->ms_total_die = ft_atoi(argv[2]);
	context->ms_eat = ft_atoi(argv[3]);
	context->ms_sleep = ft_atoi(argv[4]);
	context->ms_think = context->ms_total_die - context->ms_eat - context->ms_sleep;
	if (argc == 5)
		context->n_intakes = ft_atoi(argv[5]);
	//malloc forks and philos init
	return (context);
}

//TODO: func to destroy mutexes and join threads

// returns 1 if the given input as char* is NOT a natural number (>0)
int	is_nann(char *str)
{
	// TODO
	return (0);
}

int	check_philo_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (is_nann(argv[i]))
		{
			printf("Error: parameter %d with value %s must be a natural number", i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (check_philo_input(argc, argv))
		return (1);
	init_context(argc, argv);
	return (0);
}
