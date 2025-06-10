#include "../inc/philosophers.h"

static void	init_mutex(t_context *context)
{
	int	i;
	int	n;

	i = 0;
	n = context->n_philos;
	context->fork_locks = malloc(sizeof(pthread_mutex_t) * n);
	if (!context)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return ;
	}
	while (i < n)
	{
		pthread_mutex_init(&context->fork_locks[i], NULL);
		i++;
	}
}

t_context	*init_context(int argc, char **argv)
{
	t_context	*context;

	context = malloc(sizeof(t_context));
	if (!context)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return (NULL);
	}
	context->n_philos = ft_atoi(argv[1]);
	context->ms_ttd = ft_atoi(argv[2]);
	context->ms_eat = ft_atoi(argv[3]);
	context->ms_sleep = ft_atoi(argv[4]);
	context->ms_think = context->ms_ttd - context->ms_eat
			- context->ms_sleep;
	if (argc == 6)
		context->n_intakes = ft_atoi(argv[5]);
	context->start_ts = ft_gettime();
	init_mutex(context);
	return (context);
}

void	create_philos(t_context *context)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * context->n_philos);
	if (!philos)
	{
		write(STDERR_FILENO, "malloc error :(\n", 17);
		return ;
	}
	while (i < context->n_philos)
	{
		philos[i].id = i;
		philos[i].l_fork = i;
		philos[i].r_fork = i + 1;
		if (i + 1 == context->n_philos)
			philos[i].r_fork = 0;
		philos[i].last_meal_ts = ft_gettime() + context->ms_ttd;
		i++;
	}
	context->philos = philos; //TODO: nido de bugs y sigsevs cruzados
	philos->context = context; //TODO: nido de bugs y sigsevs cruzados
}

// TODO: create monitor to check dead philos?
void	simulation(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->context->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}

static void		finish_philos(t_context *context)
{
	int	i;

	i = 0;
	while (i < context->n_philos)
	{
		pthread_join(context->philos[i].thread, NULL);
		pthread_mutex_destroy(&context->fork_locks[i]);
		i++;
	}
}

//TODO: func to destroy mutexes and join threads
void	clear_context(t_context *context)
{
	finish_philos(context);
	pthread_mutex_destroy(&context->output);
	pthread_mutex_destroy(&context->finish_lock);
	free(context);
}