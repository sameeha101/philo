/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkforking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:53:07 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/18 18:43:53 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (*(philo->lf) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	check_right(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (*(philo->rf) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	check_da_forks(t_philo *philo)
{
	while (!check_da_ending(philo))
	{
		if (check_right(philo) || check_left(philo))
			usleep(100);
		else
			break ;
	}
	return (0);
}
