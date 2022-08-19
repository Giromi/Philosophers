/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:40:00 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/20 01:57:08 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (ERROR);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	smart_timer(int time)
{
	size_t	start;

	start = get_time();
	while (get_time() < time + start)
		usleep(100);
}

void	*monitor(void *param)
{
	size_t	now_t;
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->info.sema.print);
		now_t = get_time();
		if (now_t > philo->info.arg.die_time + philo->last_eat_t)
		{
			printf("%lu %d died\n", now_t - (*philo).info.birth_t \
					, philo->idx + 1);
			exit(1);
		}
		sem_post(philo->info.sema.print);
	}
	return (NULL);
}
