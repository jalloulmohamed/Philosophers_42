/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:10:03 by mjalloul          #+#    #+#             */
/*   Updated: 2022/05/20 19:27:34 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	routine(t_philo *philos)
{
	pthread_mutex_lock(&philos -> tab -> tabfork[philos -> id - 1]);
	philo_print("has taken a fork", get_time(), philos->id, philos);
	if (philos->id == philos->tab->nophilo)
		pthread_mutex_lock(&philos->tab->tabfork[0]);
	else
		pthread_mutex_lock(&philos->tab->tabfork[philos->id]);
	philo_print("has taken a fork", get_time(), philos->id, philos);
	philo_print("is eating", get_time(), philos->id, philos);
	ft_uslep(philos->tab->toeat);
	philos->tab->start[philos->id - 1] = get_time();
	pthread_mutex_unlock(&philos->tab->tabfork[philos->id - 1]);
	if (philos->id == philos->tab->nophilo)
		pthread_mutex_unlock(&philos->tab->tabfork[0]);
	else
		pthread_mutex_unlock(&philos->tab->tabfork[philos->id]);
	philo_print("is sleeping", get_time(), philos->id, philos);
	ft_uslep(philos->tab->toeat);
	philo_print("is thinking", get_time(), philos->id, philos);
}

void	*philosopher(void *var)
{
	int			i;
	t_philo		*philos;

	philos = (t_philo *)var;
	i = 0;
	if (philos->tab->numofarg == 5)
	{
		while (1)
			routine(philos);
	}
	else
	{
		while (i < philos->tab->notep_mush_eat)
		{
			routine(philos);
			i++;
		}
		if (i == philos->tab->notep_mush_eat)
			philos->tab->status = 1;
	}
	return (0);
}

int	checkarg(char **argv)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	if (!((ft_atoi(argv[1]) > 0 && ft_atoi(argv[1]) < 200
				&& ft_atoi(argv[2]) > 60 && ft_atoi(argv[3]) > 60
				&& ft_atoi(argv[4]) > 60) || (ft_atoi(argv[1]) > 0
				&& ft_atoi(argv[1]) < 200 && ft_atoi(argv[2]) > 60
				&& ft_atoi(argv[3]) > 60 && ft_atoi(argv[4]) > 60
				&& ft_atoi(argv[5]) >= 0)))
		return (1);
	return (0);
}

void	init_tab(t_tabphilo *tab, char**argv, int argc)
{
	tab->nophilo = ft_atoi(argv[1]);
	tab->todie = ft_atoi(argv[2]);
	tab->toeat = ft_atoi(argv[3]);
	tab->tosleep = ft_atoi(argv[4]);
	if (argc == 6)
		tab->notep_mush_eat = ft_atoi(argv[5]);
	tab->status = 0;
	tab->numofarg = argc;
	tab->starttime = get_time();
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*th_id;
	t_tabphilo	tab;
	int			i;

	i = 0;
	if (argc == 6 || argc == 5)
	{
		if (checkarg(argv) == 1)
			return (1);
		init_tab(&tab, argv, argc);
		th_id = malloc(tab.nophilo * sizeof(pthread_t));
		philo = malloc(tab.nophilo * sizeof(t_philo));
		tab.tabfork = malloc(tab.nophilo * sizeof(pthread_mutex_t));
		tab.start = malloc(tab.nophilo * sizeof(long));
		if (init_mutex(philo, &tab) == 1)
			return (1);
		if (cree_treed(th_id, &tab, philo) == 1)
			return (1);
		check_philo_dead(philo, &tab);
		destroy_mutex(philo, th_id);
	}
	else
		return (1);
}
