/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:35:41 by mjalloul          #+#    #+#             */
/*   Updated: 2022/05/20 19:45:19 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	init_mutex(t_philo *philo, t_tabphilo *tab)
{
	int	i;

	i = 0;
	while (i < tab->nophilo)
	{
		philo[i].tab = tab;
		if (pthread_mutex_init(&philo->tab->tabfork[i], NULL) != 0)
			return (1);
		pthread_mutex_init(&philo->tab->tabfork[i], NULL);
		philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int	cree_treed(pthread_t *th_id, t_tabphilo *tab, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < tab->nophilo)
	{
		if (pthread_create(&th_id[i], NULL, philosopher,
				(void *)&philo[i]) != 0)
			return (1);
		tab->start[i] = get_time();
		usleep(100);
		i++;
	}
	return (0);
}

void	check_philo_dead(t_philo *philo, t_tabphilo *tab)
{
	int	i;

	i = 0;
	while (i < tab->nophilo)
	{
		if (get_time() - philo[i].tab->start[philo[i].id - 1]
			> philo[i].tab->todie)
		{
			pthread_mutex_lock(&philo[i].tab->print);
			if (tab->status == 0)
				printf("[%ld] philo %d  died\n", get_time()
					- tab->starttime, philo[i].id);
			break ;
		}
		i++;
		if (i == tab->nophilo)
			i = 0;
	}
}

void	destroy_mutex(t_philo *philo, pthread_t	*th_id)
{
	int	i;

	i = 0;
	while (i < philo->tab->nophilo)
	{
		pthread_mutex_destroy(&philo->tab->tabfork[i]);
		pthread_detach(th_id[i]);
		i++;
	}
	free(philo);
}
