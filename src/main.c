/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:21 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/07 19:36:28 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	(void)arg;
	printf("viva vox\n");
	return (NULL);
}

t_context	*init_context(int argc, char **argv)
{
	t_context	*context;
	int		i;

	context = malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->n_philos = ft_atoi(argv[1]);
	context->ms_total_die = ft_atoi(argv[2]);
	context->ms_eat = ft_atoi(argv[3]);
	context->ms_sleep = ft_atoi(argv[4]);
	context->ms_think = context->ms_total_die - context->ms_eat
			- context->ms_sleep;
	if (argc == 6)
		context->n_intakes = ft_atoi(argv[5]);
	i = 0;
	context->threads = malloc(sizeof(pthread_t) * context->n_philos);
	if (!context->threads)
		return (NULL);
	while (i < context->n_philos)
	{
		pthread_create(&context->threads[i], NULL, routine, NULL);
		i++;
	}
	//malloc forks and philos init
	return (context);
}

//TODO: func to destroy mutexes and join threads
void	clear_context(t_context *context)
{
	int	i;

	i = 0;
	while (i < context->n_philos)
	{
		pthread_join(context->threads[i], NULL);
		i++;
	}
	free(context->threads);
}

// returns 1 if the given input as char* is NOT a natural number (>0)
int	is_nann(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_philo_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (is_nann(argv[i]))
		{
			printf("Error: parameter %d with value \"%s\" must be a"
				" natural number\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_context	*context;

	if (check_philo_input(argc, argv))
		return (1);
	context = init_context(argc, argv);
	//free context OR destroy everything
	clear_context(context);
	free(context);
	return (0);
}
