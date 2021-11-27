#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define RESET "\x1b[0m"

typedef struct s_info
{
	unsigned int	numb_of_phil;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_must_eat;
}				t_info;

typedef struct s_table
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	take;
	pthread_mutex_t	print;
	int				all_eat;
	time_t			start;
}				t_table;

typedef struct s_phil
{
	unsigned int	num;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	num_meal;
	time_t			last_meal;
	time_t			hp;
	int				dead;
}				t_phil;

typedef struct s_arg
{
	t_info	*info;
	t_phil	*phil;
	t_table	*table;
}	t_arg;

int		ft_atoi(const char *src);
int		parser(int ac, char **av, t_info *info);
int		start_philo(t_arg *args);
void	my_sleep(time_t time);
void	*routine(void *arg);
int		dead_check(t_table *table, t_phil *phil, t_arg *arg);
time_t	get_time(time_t start);
void	print_msg(t_arg *arg, char *msg, char *cod);

#endif