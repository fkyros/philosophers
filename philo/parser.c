/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:23:23 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/10 18:35:17 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

long	ft_atoi(const char *nptr)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		res *= 10;
		res += (nptr[i] - '0');
		i++;
	}
	if (i > 11)
		return (-1);
	return (res);
}

// returns 1 if the given input as char* is NOT a natural number (>0)
// or superior to MAX_INT
int	check_philo_input(int argc, char **argv)
{
	int	i;
	int	parsed_num;

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
		parsed_num = ft_atoi(argv[i]);
		if (parsed_num <= 0 || parsed_num > INT_MAX)
		{
			printf("Error: parameter %d with value \"%s\" must be a"
				" natural number\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
