#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define VAL_INT_MAX			2147483647
# define VAL_INT_MIN			2147483648

typedef struct s_status
{
	int	end;
	int	n_full;
}	t_status;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t print;
}	t_mutex;

typedef struct s_arg
{
	int	n_philo;
	int die_time;
	int eat_time;
	int sleep_time;
	int must_eat;
}	t_arg;

typedef struct s_info
{
	t_arg		arg;
	t_mutex 	mutex;
	t_status 	stat;
	size_t		birth_t;
}	t_info;

typedef struct s_philo
{
	int				idx;
	pthread_t		tid;
	int				cnt_eat;
	size_t			last_eat_t;
	t_info			*info;
	pthread_mutex_t	*mtx_left;
	pthread_mutex_t	*mtx_right;
}	t_philo;

enum e_enum
{
	ERROR = -1,
	SUCCESS,
	EATTING
};

size_t		get_time();
void		smart_timer(int time);
void		monitor(t_philo *philo);
void		mutex_free(t_philo *philo, t_mutex *mutex);
void		*action(void *param);
int			ft_postive_atoi(const char *str);
int			ft_error(char *str);
#endif
