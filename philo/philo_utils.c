/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 07:54:49 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/17 10:54:17 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	smart_timer(int time)
{
	size_t	start;

	start = get_time();
	while (get_time() < time + start )
		usleep(100);
}

void	monitor(t_philo *philo)
{
	int	i;
	int	kill_;

	kill_ = 0;
	while (1)
	{
		i = 0;
		while (i < philo->info->arg.n_philo)
		{
			pthread_mutex_lock(&philo->info->mutex.print);
			kill_ = philo->info->stat.end;
			if (get_time() > philo->info->arg.die_time + philo[i].last_eat_t )
			{
				philo->info->stat.end++;
				printf("%ld %d died\n", get_time() - philo->info->birth_t, i + 1);
				pthread_mutex_unlock(&philo->info->mutex.print);
				return ;
			}
			else
				pthread_mutex_unlock(&philo->info->mutex.print);
			if (kill_)
				return ;
			++i;
		}
	}
}

void	mutex_free(t_philo *philo, t_mutex *mutex)
{
	int i;

	i = -1;
	while (++i < philo->info->arg.n_philo)
		pthread_mutex_destroy(philo[i].left);
	pthread_mutex_destroy(&mutex->print);
	free((*mutex).fork);
	free(philo);
}
