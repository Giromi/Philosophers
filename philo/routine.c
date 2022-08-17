/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 07:56:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/17 14:49:41 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_print(t_philo *philo, int idx, char *str, int eat_status)
{
	size_t	now_t;

	pthread_mutex_lock(&philo->info->mutex.print);
	if (philo->info->stat.end == 0)
	{
		now_t = get_time();
		printf("%ld %d %s\n", now_t - philo->info->birth_t, idx + 1, str);
		if (eat_status)
		{
			philo->last_eat_t = now_t;
			if (++(philo->cnt_eat) == philo->info->arg.must_eat)
			{
				philo->info->stat.n_full++;
				if (philo->info->stat.n_full == philo->info->arg.n_philo)
					philo->info->stat.end++;
			}
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->info->mutex.print);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->info->mutex.print);
	return (SUCCESS);
}

static int	take_fork(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(philo->mtx_left);
		if (philo_print(philo, philo->idx, "has taken a fork", 0))
			return (ERROR);
		pthread_mutex_lock(philo->mtx_right);
		if (philo_print(philo, philo->idx, "has taken a fork", 0))
			return (ERROR);
	}
	else
	{
		pthread_mutex_lock(philo->mtx_right);
		if (philo_print(philo, philo->idx, "has taken a fork", 0))
			return (ERROR);
		pthread_mutex_lock(philo->mtx_left);
		if (philo_print(philo, philo->idx, "has taken a fork", 0))
			return (ERROR);
	}
	return (SUCCESS);
}

static int	eating(t_philo *philo, t_arg *arg)
{
	if (philo_print(philo, philo->idx, "is eating", EATTING))
		return (ERROR);
	smart_timer(arg->eat_time);
	return (SUCCESS);
}

static int	sleep_thinking(t_philo *philo, t_arg *arg)
{
	pthread_mutex_unlock(philo->mtx_right);
	pthread_mutex_unlock(philo->mtx_left);
	if (philo_print(philo, philo->idx, "is sleeping", 0))
		return (ERROR);
	smart_timer(arg->sleep_time);
	if (philo_print(philo, philo->idx, "is thinking", 0))
		return (ERROR);
	return (SUCCESS);
}

void	*action(void *param)
{
	t_philo	*philo;
	philo = (t_philo *)param;

	pthread_mutex_lock(&philo->info->mutex.print);
	(*philo).last_eat_t = get_time();
	pthread_mutex_unlock(&philo->info->mutex.print);
	if (philo->idx % 2 != 0)
		smart_timer(philo->info->arg.eat_time / 2);
	while (!take_fork(philo)
		 && !eating(philo, &philo->info->arg)
		 && !sleep_thinking(philo, &philo->info->arg));
	return (NULL);
}
