/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:16:11 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/20 03:33:33 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_print(t_philo *philo, int idx, char *str, int eat_status)
{
	size_t	now_t;

	sem_wait(philo->info.sema.print);
	now_t = get_time();
	printf("%ld %d %s\n", now_t - philo->info.birth_t, idx + 1, str);
	if (eat_status)
	{
		philo->last_eat_t = now_t;
		if (++(philo->eat_cnt) == philo->info.arg.must_eat)
		{
			sem_post(philo->info.sema.eat_checker);
			return ;
		}
	}
	sem_post(philo->info.sema.print);
}

static int	take_fork(t_philo *philo)
{
	sem_wait(philo->info.sema.fork);
	philo_print(philo, philo->idx, "has taken a fork", 0);
	sem_wait(philo->info.sema.fork);
	philo_print(philo, philo->idx, "has taken a fork", 0);
	return (SUCCESS);
}

static int	eating(t_philo *philo)
{
	philo_print(philo, philo->idx, "is eating", EATTING);
	smart_timer((*philo).info.arg.eat_time);
	return (SUCCESS);
}

static int	sleep_thinking(t_philo *philo)
{
	sem_post(philo->info.sema.fork);
	sem_post(philo->info.sema.fork);
	philo_print(philo, philo->idx, "is sleeping", 0);
	smart_timer(philo->info.arg.sleep_time);
	philo_print(philo, philo->idx, "is thinking", 0);
	usleep(50);
	return (SUCCESS);
}

void	action(t_philo philo)
{
	pthread_t	monitor_tid;

	philo.last_eat_t = get_time();
	pthread_create(&monitor_tid, NULL, monitor, &philo);
	while (!take_fork(&philo)
		&& !eating(&philo)
		&& !sleep_thinking(&philo));
	exit(1);
}
