/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:01:00 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/20 02:02:08 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# define VAL_INT_MAX			2147483647
# define VAL_INT_MIN			2147483648

typedef struct s_sem
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*eat_checker;
}	t_sem;

typedef struct s_arg
{
	int		die_time;
	int		n_philo;
	int		eat_time;
	int		sleep_time;
	int		must_eat;
}	t_arg;

typedef struct s_info
{
	t_arg		arg;
	t_sem		sema;
	size_t		birth_t;
	pid_t		*pid;
}	t_info;

typedef struct s_philo
{
	int		idx;
	t_info	info;
	size_t	last_eat_t;
	int		eat_cnt;
}	t_philo;

enum e_enum
{
	ERROR = -1,
	SUCCESS,
	EATTING
};

size_t	get_time(void);
void	smart_timer(int time);
int		ft_error(char *str);
void	*monitor(void *param);
void	action(t_philo philo);
int		ft_postive_atoi(const char *str);
#endif
