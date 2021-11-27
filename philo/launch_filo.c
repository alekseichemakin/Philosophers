#include "includes/philo.h"

void	print_all_eat(t_arg *arg)
{
	pthread_mutex_lock(&arg->table->print);
	printf(GREEN"ALL EAT MINIMUM: %d times\n"RESET,
		   arg->info->times_must_eat);
}

void	*dead_monitor(void *args)
{
	int		i;
	t_arg	*arg;

	usleep(10);
	arg = (t_arg *)args;
	while (1)
	{
		i = -1;
		while (++i < (int)arg->info->numb_of_phil)
		{
			if (dead_check(arg->table, &arg->phil[i], arg))
			{
				pthread_mutex_lock(&arg->table->print);
				printf(RED"[%ld ms] Philo: %d [is died] R.I.P.\n"RESET, get_time
					(arg->table->start), i + 1);
				return (NULL);
			}
			if (arg->table->all_eat == (int)arg->info->numb_of_phil)
			{
				print_all_eat(arg);
				return (NULL);
			}
		}
	}
}

int	free_args(t_arg *args)
{
	int	i;

	i = -1;
	while (++i < (int)args->info->numb_of_phil)
		if (pthread_mutex_destroy(&args->table->fork[i]))
			return (1);
	if (pthread_mutex_destroy(&args->table->print))
		return (1);
	if (pthread_mutex_destroy(&args->table->take))
		return (1);
	free(args->phil);
	free(args->info);
	free(args->table);
	free(args);
	return (0);
}

int	anybody_dead(t_arg *args, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < (int)args->info->numb_of_phil)
		if (pthread_detach(threads[i]) != 0)
			return (1);
	free_args(args);
	return (0);
}

int	start_philo(t_arg *args)
{
	int			i;
	pthread_t	*threads;
	pthread_t	monitor;

	i = -1;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->info->numb_of_phil);
	if (threads == NULL)
		return (1);
	while (++i < (int)args->info->numb_of_phil)
		if (pthread_create(&threads[i], NULL, &routine, &(args[i])))
			return (1);
	if (pthread_create(&monitor, NULL, &dead_monitor, args))
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	else
	{
		anybody_dead(args, threads);
		free(threads);
		return (0);
	}
	return (0);
}
