#include "includes/philo.h"

void	print_msg(t_arg *arg, char *msg, char *cod)
{
	pthread_mutex_lock(&arg->table->print);
	printf("[%ld ms] Philo: %d", get_time(arg->table->start),
		   arg->phil->num + 1);
	printf(" [%s%s%s]\n", cod, msg, RESET);
	pthread_mutex_unlock(&arg->table->print);
}

void	my_sleep(time_t time)
{
	struct timeval	tv;
	time_t			start;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (time > (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start)
	{
		gettimeofday(&tv, NULL);
		usleep(50);
	}
}

int	ft_atoi(const char *src)
{
	int	out;
	int	sign;

	out = 0;
	sign = 1;
	while (*src == '\t' || *src == '\n' || *src == '\v' || *src == '\f'
		   || *src == '\r' || *src == ' ')
		src++;
	if (*src == '-')
	{
		sign = -1;
		src++;
	}
	else if (*src == '+')
		src++;
	if (*src >= '0' && *src <= '9')
	{
		while (*src >= '0' && *src <= '9' && *src)
		{
			out = (out * 10) + (*src - '0');
			src++;
		}
		return (sign * out);
	}
	return (0);
}
