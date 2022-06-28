/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:18:05 by mjalloul          #+#    #+#             */
/*   Updated: 2022/06/27 23:18:06 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_print(char *str, long time, int id, t_philo *philos)
{
	sem_wait(philos->tab->print);
	printf("[%ld] philo %d  %s\n", time - philos->starttime, id, str);
	sem_post(philos->tab->print);
	return ;
}
