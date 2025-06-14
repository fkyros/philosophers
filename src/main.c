/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:21 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/14 16:31:32 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_context	*context;
	t_philo		*philos;

	if (check_philo_input(argc, argv))
		return (1);
	context = init_context(argc, argv);
	//if !context
	// TODO: include fifth argument behaviour to finish simulation
	philos = create_philos(context);
	//if !philos
	simulation(context, philos);
	clear_context(philos, context);
	return (0);
}
