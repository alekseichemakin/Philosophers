#include "includes/philo_bonus.h"

int	init_sem(t_table *table, t_info *info)
{
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	sem_unlink("sem_dead");
	sem_unlink("sem_eat");
	sem_unlink("1");
	table->print = sem_open("sem_print", O_CREAT, 0777, 1);
	table->dead = sem_open("sem_dead", O_CREAT, 0777, 0);
	table->fork = sem_open("sem_fork", O_CREAT, 0777, info->numb_of_phil);
	table->chekc = sem_open("1", O_CREAT, 0777, 1);
	if (table->print == SEM_FAILED || table->fork == SEM_FAILED)
		return (1);
	return (0);
}

int	init_table(t_table *table, t_info *info, t_phil *phil, t_arg *arg)
{
	size_t	i;

	if (init_sem(table, info))
		return (1);
	i = -1;
	while (++i < info->numb_of_phil)
	{
		(phil[i]).num = i;
		(phil[i]).last_meal = 0;
		(phil[i]).dead = 0;
		(phil[i]).num_meal = 0;
		(phil[i]).eat = sem_open("sem_eat", O_CREAT, 0777, 0);
	}
	i = -1;
	while (++i < info->numb_of_phil)
	{
		arg[i].table = table;
		arg[i].phil = &phil[i];
		arg[i].info = info;
	}
	return (0);
}

void	*dead_monitor(void *args)
{
	t_arg	*arg;

	arg = (t_arg *)args;
	while (1)
	{
		sem_wait(arg->table->chekc);
		arg->phil->hp = arg->phil->last_meal + arg->info->time_to_die
			- get_time(arg->table->start);
		sem_post(arg->table->chekc);
		if (arg->phil->hp <= 0)
		{
			arg->phil->dead = 1;
			sem_wait(arg->table->print);
			printf(RED"[%ld ms] Philo: %d [is died] R.I.P.\n"RESET, get_time
				(arg->table->start), arg->phil->num + 1);
			sem_post(arg->table->dead);
			return (NULL);
		}
	}
}

void	get_fork(t_arg *arg)
{
	sem_wait(arg->table->fork);
	print_msg(arg, "take fork", "");
	sem_wait(arg->table->fork);
	arg->phil->last_meal = get_time(arg->table->start);
	print_msg(arg, "take fork", "");
	print_msg(arg, "is eating", GREEN);
	my_sleep(arg->info->time_to_eat);
	arg->phil->num_meal++;
	if (arg->phil->num_meal == arg->info->times_must_eat)
		sem_post(arg->phil->eat);
	sem_post(arg->table->fork);
	sem_post(arg->table->fork);
	print_msg(arg, "is sleeping", BLUE);
	my_sleep(arg->info->time_to_sleep);
	print_msg(arg, "is thinking", YELLOW);
}

void	*eat(t_arg *arg)
{
	struct timeval	tv;
	pthread_t		monitor;

	gettimeofday(&tv, NULL);
	arg->table->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_create(&monitor, NULL, &dead_monitor, arg);
	pthread_detach(monitor);
	if (arg->phil->num % 2 == 0)
		my_sleep(arg->info->time_to_eat);
	while (arg->phil->dead == 0)
		get_fork(arg);
	return (NULL);
}
