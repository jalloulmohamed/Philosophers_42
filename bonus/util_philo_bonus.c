/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:35:41 by mjalloul          #+#    #+#             */
/*   Updated: 2022/06/27 23:33:13 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal > philo->tab->todie)
		{
			sem_wait(philo->tab->print);
			printf("philo %d died\n", philo->id);
			break ;
		}
	}
	exit(0);
	return (NULL);
}

void	kill_process(pid_t *pid, t_tabphilo tab)
{
	int	j;
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (i < tab.nophilo)
	{
		waitpid(-1, &j, 0);
		if (WEXITSTATUS(j) == 0 || WEXITSTATUS(j) == 1)
		{
			while (x < tab.nophilo)
			{
				kill(pid[x], SIGKILL);
				x++;
			}
		}
		i++;
	}
}

void	creation_process(t_philo *philo, t_tabphilo tab, pid_t *pid )
{
	pthread_t	th;
	int			i;

	i = 0;
	while (i < tab.nophilo)
	{
		philo[i].id = i + 1;
		philo[i].tab = &tab;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			philo[i].starttime = get_time();
			philo[i].last_meal = get_time();
			pthread_create(&th, NULL, check_death, &philo[i]);
			philosopher(&philo[i]);
			return ;
		}
		i++;
	}
}
