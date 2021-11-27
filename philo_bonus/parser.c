#include "includes/philo_bonus.h"

int	check_digit(char **av)
{
	int	i;
	int	n;

	i = 0;
	while (av[++i])
	{
		n = -1;
		while (av[i][++n])
			if (av[i][n] < '0' || av[i][n] > '9')
				return (1);
	}
	return (0);
}

int	get_info(char **av, t_info *info)
{
	info->numb_of_phil = ft_atoi(av[1]);
	if (info->numb_of_phil <= 0)
		return (1);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->times_must_eat = ft_atoi((av[5]));
	else
		info->times_must_eat = 0;
	return (0);
}

int	parser(int ac, char **av, t_info *info)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (check_digit(av))
		return (1);
	if (get_info(av, info))
		return (1);
	return (0);
}
