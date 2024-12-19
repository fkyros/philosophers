/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:21 by gade-oli          #+#    #+#             */
/*   Updated: 2024/12/19 17:07:12 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/philosophers.h"

int	a = 0;

void *semen(void *ex)
{
	if (!a)
		printf("no hay semen!!!\n");
	pthread_mutex_lock(ex);
	a++;
	printf("semen = %d\n", a);
	pthread_mutex_unlock(ex);
	return (NULL);
}

t_list	*init_threads(int n, int ms_sleep, int ms_think, int ms_eat)
{
	int	i;
	t_list	*list;

	list = ft_lstnew(init_philo(ms_sleep, ms_think, ms_eat));
	i = 1;
	while (i < n)
	{
		ft_lstadd_back(&list, ft_lstnew(init_philo(ms_sleep, ms_think, ms_eat)));
		i++;
	}
	return (list);
}

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

int main(void)
{
	pthread_mutex_t	ex;
	pthread_t		t1;
	pthread_t		t2;

	pthread_mutex_init(&ex, NULL);
	if (pthread_create(&t1, NULL, &semen, &ex))
		return (1);
	if (pthread_create(&t2, NULL, &semen, &ex))
		return (1);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&ex);
	return (0);
}
