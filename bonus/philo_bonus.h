/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:17:32 by mjalloul          #+#    #+#             */
/*   Updated: 2022/06/27 23:28:28 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <semaphore.h>
# include <signal.h>

typedef struct tabphilo {
	int					nophilo;
	int					todie;
	int					toeat;
	int					tosleep;
	int					notep_mush_eat;
	sem_t				*fork;
	sem_t				*print;
	int					numofarg;
}	t_tabphilo;

typedef struct philo{
	t_tabphilo	*tab;
	int			id;
	long		last_meal;
	long		starttime;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
long	get_time(void);
void	philo_print(char *str, long time, int id, t_philo *philos);
void	check_philo_dead(t_philo *philo, t_tabphilo *tab);
void	ft_uslep(int time);
void	*check_death(void *arg);
void	kill_process(pid_t *pid, t_tabphilo tab);
void	creation_process(t_philo *philo, t_tabphilo tab, pid_t *pid);
void	philosopher(t_philo *philos);

#endif