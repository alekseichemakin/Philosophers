#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
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
	sem_t			*fork;
	sem_t			*dead;
	sem_t			*print;
	sem_t			*chekc;
	time_t			start;
}				t_table;

typedef struct s_phil
{
	unsigned int	num;
	unsigned int	num_meal;
	time_t			last_meal;
	time_t			hp;
	int				dead;
	sem_t			*eat;
}				t_phil;

typedef struct s_arg
{
	t_info	*info;
	t_phil	*phil;
	t_table	*table;
}	t_arg;

int		parser(int ac, char **av, t_info *info);
int		ft_atoi(const char *src);
void	my_sleep(time_t time);
void	print_msg(t_arg *arg, char *msg, char *cod);
time_t	get_time(time_t start);
void	*eat(t_arg *arg);
void	*eat_monitor(void *args);
int		init_table(t_table *table, t_info *info, t_phil *phil, t_arg *arg);

#endif
