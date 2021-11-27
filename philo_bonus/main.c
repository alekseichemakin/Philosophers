#include "includes/philo_bonus.h"

void	kill_all(int *pid, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (int)arg->info->numb_of_phil)
		kill(pid[i], SIGKILL);
	sem_close(arg->table->print);
	sem_close(arg->table->dead);
	sem_close(arg->table->fork);
	free(pid);
}

int	launch_philo2(t_arg *arg)
{
	int			i;
	int			*pid;
	pthread_t	monitor;

	i = -1;
	pid = malloc(sizeof(int) * (int)arg->info->numb_of_phil);
	while (++i < (int)arg->info->numb_of_phil)
	{
		pid[i] = fork();
		if (pid < 0)
			exit (1);
		if (pid[i] == 0)
		{
			eat(&arg[i]);
			exit(1);
		}
	}
	pthread_create(&monitor, NULL, &eat_monitor, arg);
	sem_wait(arg->table->dead);
	kill_all(pid, arg);
	exit (0);
}

int	launch_philo(t_info *info)
{
	t_phil	*phil;
	t_table	*table;
	t_arg	*arg;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (1);
	phil = (t_phil *)malloc(sizeof(t_phil) * info->numb_of_phil);
	if (!phil)
		return (1);
	arg = (t_arg *)malloc(sizeof(t_arg) * info->numb_of_phil);
	if (!arg)
		return (1);
	if (init_table(table, info, phil, arg))
		return (1);
	i = -1;
	while (++i < (int)info->numb_of_phil)
	{
		arg[i].table = table;
		arg[i].phil = &phil[i];
		arg[i].info = info;
	}
	launch_philo2(arg);
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
