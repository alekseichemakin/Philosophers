#include "includes/philo.h"

time_t	get_time(time_t start)
{
	struct timeval	tv;
	time_t			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start;
	return (res);
}

int	dead_check(t_table *table, t_phil *phil, t_arg *arg)
{
	phil->hp = phil->last_meal + arg->info->time_to_die
		- get_time(table->start);
	if (phil->hp <= 0)
		phil->dead = 1;
	return (phil->dead);
}

void	eat_process(t_phil *phil, t_table *table, t_arg *arg)
{
	phil->last_meal = get_time(table->start);
	print_msg(arg, "is eating", GREEN);
	phil->num_meal++;
	pthread_mutex_lock(&table->take);
	if (phil->num_meal == arg->info->times_must_eat
		&& arg->info->times_must_eat != 0)
		table->all_eat++;
	pthread_mutex_unlock(&table->take);
	my_sleep(arg->info->time_to_eat);
	pthread_mutex_unlock(&table->fork[phil->right_fork]);
	pthread_mutex_unlock(&table->fork[phil->left_fork]);
	print_msg(arg, "is sleeping", BLUE);
	my_sleep(arg->info->time_to_sleep);
	print_msg(arg, "is thinking", YELLOW);
}

void	*routine(void *args)
{
	t_arg			*arg;
	t_phil			*phil;
	t_table			*table;
	struct timeval	tv;

	arg = (t_arg *)args;
	phil = arg->phil;
	table = arg->table;
	gettimeofday(&tv, NULL);
	table->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (phil->num % 2 == 0)
		my_sleep(arg->info->time_to_eat);
	while (table->all_eat != (int)arg->info->numb_of_phil)
	{
		pthread_mutex_lock(&table->fork[phil->left_fork]);
		print_msg(arg, "has taken a fork", "");
		pthread_mutex_lock(&table->fork[phil->right_fork]);
		print_msg(arg, "has taken a fork", "");
		eat_process(phil, table, arg);
	}
	return (NULL);
}
