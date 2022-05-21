/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:31:47 by mjalloul          #+#    #+#             */
/*   Updated: 2022/05/20 19:35:15 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct tabphilo {
	int					nophilo;
	int					todie;
	int					toeat;
	int					tosleep;
	int					notep_mush_eat;
	pthread_mutex_t		*tabfork;
	long				*start;
	int					status;
	int					numofarg;
	long				starttime;
	pthread_mutex_t		print;
}	t_tabphilo;

typedef struct philo{
	t_tabphilo	*tab;
	int			id;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
long	get_time(void);
void	philo_print(char *str, long time, int id, t_philo *philos);
void	routine(t_philo *philos);
void	*philosopher(void *var);
int		init_mutex(t_philo *philo, t_tabphilo *tab);
int		cree_treed(pthread_t *th_id, t_tabphilo *tab, t_philo *philo);
void	check_philo_dead(t_philo *philo, t_tabphilo *tab);
void	destroy_mutex(t_philo *philo, pthread_t	*th_id);
void	ft_uslep(int time);

#endif
