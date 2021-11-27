#include "includes/philo.h"

void	init_philo(t_info *info, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < (int)info->numb_of_phil)
	{
		phil[i].num = i;
		phil[i].num_meal = 0;
		phil[i].num_meal = 0;
		phil[i].hp = info->time_to_die;
		phil[i].dead = 0;
		phil[i].left_fork = i;
		phil[i].last_meal = 0;
		if (i == 0)
			phil[i].right_fork = info->numb_of_phil - 1;
		else
			phil[i].right_fork = i - 1;
	}
}

int	init_mutex(t_phil *phil, t_table *table, t_arg *arg, t_info *info)
{
	int	i;

	i = -1;
	while (++i < (int)info->numb_of_phil)
		if (pthread_mutex_init(&(table->fork[i]), NULL))
			return (1);
	pthread_mutex_init(&table->take, NULL);
	pthread_mutex_init(&table->print, NULL);
	table->all_eat = 0;
	init_philo(info, phil);
	i = -1;
	while (++i < (int)info->numb_of_phil)
	{
		arg[i].table = table;
		arg[i].phil = &phil[i];
		arg[i].info = info;
	}
	return (0);
}

int	launch_philo(t_info *info)
{
	t_phil	*phil;
	t_table	*table;
	t_arg	*arg;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (1);
	phil = (t_phil *)malloc(sizeof(t_phil) * info->numb_of_phil);
	if (!phil)
		return (1);
	arg = (t_arg *)malloc(sizeof(t_arg) * info->numb_of_phil);
	if (!arg)
		return (1);
	table->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->numb_of_phil);
	if (!table->fork)
		return (1);
	init_mutex(phil, table, arg, info);
	start_philo(arg);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (parser(argc, argv, &info))
	{
		printf(RED "wrong start parametr\n" RESET);
		return (1);
	}
	if (launch_philo(&info))
	{
		printf(RED "Error: philosophers can't launch\n" RESET);
		return (1);
	}
	return (0);
}
