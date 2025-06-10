#include "../inc/philosophers.h"

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
	//context = 
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
