/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uslep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 22:46:10 by mjalloul          #+#    #+#             */
/*   Updated: 2022/05/20 22:47:58 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	long	apah(long long pers, long long past)
{
	return (pers - past);
}

void	ft_uslep(int time)
{
	long long	start_resting;

	start_resting = get_time();
	while (1)
	{
		if (apah(get_time(), start_resting) >= time)
			break ;
		usleep(500);
	}
}
