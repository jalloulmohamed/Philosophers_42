/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:10:03 by mjalloul          #+#    #+#             */
/*   Updated: 2022/06/27 23:20:06 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philos)
{
	sem_wait(philos->tab->fork);
	philo_print("has taken a fork", get_time(), philos->id, philos);
	sem_wait(philos->tab->fork);
	philo_print("has taken a fork", get_time(), philos->id, philos);
	philo_print("is eating", get_time(), philos->id, philos);
	ft_uslep(philos->tab->toeat);
	philos->last_meal = get_time();
	sem_post(philos->tab->fork);
	sem_post(philos->tab->fork);
	philo_print("is sleeping", get_time(), philos->id, philos);
	ft_uslep(philos->tab->tosleep);
	philo_print("is thinking", get_time(), philos->id, philos);
}

void	philosopher(t_philo *philos)
{
	int			i;

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
		exit(1);
	}
}

void	init_tab(t_tabphilo *tab, char**argv, int argc)
{
	tab->nophilo = ft_atoi(argv[1]);
	tab->todie = ft_atoi(argv[2]);
	tab->toeat = ft_atoi(argv[3]);
	tab->tosleep = ft_atoi(argv[4]);
	if (argc == 6)
		tab->notep_mush_eat = ft_atoi(argv[5]);
	tab->numofarg = argc;
	sem_unlink("fork");
	tab->fork = sem_open("fork", O_CREAT, 0, ft_atoi(argv[1]));
	sem_unlink("print");
	tab->print = sem_open("print", O_CREAT, 0, 1);
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

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_tabphilo	tab;
	pid_t		*pid;

	if (argc == 6 || argc == 5)
	{
		if (checkarg(argv) == 1)
			return (1);
		init_tab(&tab, argv, argc);
		philo = malloc(tab.nophilo * sizeof(t_philo));
		pid = malloc(tab.nophilo * sizeof(int));
		creation_process(philo, tab, pid);
		kill_process(pid, tab);
	}
	else
		return (1);
}
