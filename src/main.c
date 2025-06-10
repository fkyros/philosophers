/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:21 by gade-oli          #+#    #+#             */
/*   Updated: 2025/06/11 00:39:11 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_context	*context;

	if (check_philo_input(argc, argv))
		return (1);
	context = init_context(argc, argv);
	// TODO: include fifth argument behaviour to finish simulation
	create_philos(context);
	simulation(context->philos);
	clear_context(context);
	return (0);
}
