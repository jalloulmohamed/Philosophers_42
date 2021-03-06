/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:29:47 by mjalloul          #+#    #+#             */
/*   Updated: 2022/06/28 16:47:32 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(char *str, long time, int id, t_philo *philos)
{
	pthread_mutex_lock(&philos->tab->print);
	printf("[%ld] philo %d  %s\n", time - philos->tab->starttime, id, str);
	pthread_mutex_unlock(&philos->tab->print);
	return ;
}
