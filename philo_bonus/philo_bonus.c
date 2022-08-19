/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:36:51 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/20 01:55:36 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*eat_checker(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	i = -1;
	while (++i < philo->info.arg.n_philo)
	{
		sem_wait(philo->info.sema.eat_checker);
		if (i + 1 == philo->info.arg.n_philo)
			break ;
		sem_post(philo->info.sema.print);
	}
	i = -1;
	while (++i < philo->info.arg.n_philo)
		kill(philo->info.pid[i], SIGKILL);
	sem_close(philo->info.sema.eat_checker);
	sem_unlink("eat_checker");
	return (NULL);
}

int	init_info(int argc, t_philo *philo, t_info *info, t_arg *arg)
{
	int	idx;

	sem_unlink("sem_fork");
	info->sema.fork = sem_open("sem_fork", O_CREAT | O_EXCL, 0644 \
			, arg->n_philo);
	sem_unlink("sem_print");
	info->sema.print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("sem_eat_checker");
	if (argc == 6)
		info->sema.eat_checker = sem_open("sem_eat_checker", O_CREAT | O_EXCL \
				, 0644, 0);
	idx = 0;
	info->birth_t = get_time();
	while (idx < info->arg.n_philo)
	{
		info->pid[idx] = fork();
		if (info->pid[idx] == 0)
			action(*philo);
		philo->idx = ++idx;
	}
	return (SUCCESS);
}

static int	parse_arg(int argc, char **argv, t_info *info)
{
	if (!(argc == 5 || argc == 6))
		return (ft_error("argument count"));
	info->arg.n_philo = ft_postive_atoi(argv[1]);
	if (info->arg.n_philo <= 0)
		return (ft_error("philosophers_n argument"));
	info->arg.die_time = ft_postive_atoi(argv[2]);
	info->arg.eat_time = ft_postive_atoi(argv[3]);
	info->arg.sleep_time = ft_postive_atoi(argv[4]);
	if (info->arg.die_time <= 0 || info->arg.eat_time <= 0
		|| info->arg.sleep_time <= 0)
		return (ft_error("time argument"));
	info->arg.must_eat = 0;
	if (argc == 6)
	{
		info->arg.must_eat = atoi(argv[5]);
		if (info->arg.must_eat <= 0)
			return (ft_error("must_eat_n argument"));
	}
	return (SUCCESS);
}

void	sema_fclean(t_info *info, t_sem *sema, t_arg *arg)
{
	int	i;

	waitpid(-1, 0, 0);
	i = -1;
	while (++i < arg->n_philo)
		kill(info->pid[i], SIGKILL);
	sem_close(sema->fork);
	sem_close(sema->print);
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	free(info->pid);
	while (--i)
		waitpid(-1, 0, 0);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	tid_eatchecker;

	memset(&philo, 0, sizeof(t_philo));
	if (parse_arg(argc, argv, &philo.info) == ERROR)
		return (ERROR);
	philo.info.pid = malloc(sizeof(pid_t) * philo.info.arg.n_philo);
	if (!philo.info.pid)
		return (ERROR);
	if (!init_info(argc, &philo, &philo.info, &philo.info.arg) && argc == 6)
	{
		pthread_create(&tid_eatchecker, NULL, eat_checker, &philo);
		pthread_detach(tid_eatchecker);
	}
	sema_fclean(&philo.info, &philo.info.sema, &philo.info.arg);
	return (0);
}
