/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:41:16 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 16:05:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_rf(t_philo *philo)
{
	while (!check_da_ending(philo))
	{
		if (check_right(philo))
			ft_usleep(100, philo);
		else
			break ;
	}
	pthread_mutex_lock(philo->r_fork);
	*(philo->rf) = 1;
	pthread_mutex_unlock(philo->r_fork);
	if (!check_da_ending(philo))
		printing(philo, "has taken a fork\n");
	return (0);
}

int	take_lf(t_philo *philo)
{
	while (!check_da_ending(philo))
	{
		if (check_left(philo))
			ft_usleep(100, philo);
		else
			break ;
	}
	pthread_mutex_lock(philo->l_fork);
	*(philo->lf) = 1;
	pthread_mutex_unlock(philo->l_fork);
	if (!check_da_ending(philo))
		printing(philo, "has taken a fork\n");
	return (0);
}
int	taking_forks(t_philo *philo)
{
	// int	f;

	// f = 0;
	if (!check_right(philo))
	{
		take_rf(philo);
		// f = 1;
	}
	if (!check_left(philo))
	{
		take_lf(philo);
		// f = 2;
	}
	// if (f == 1)
	// 	take_lf(philo);
	// else if (f == 2)
	// 	take_rf(philo);
	return (0);
}

int	dropping_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	*(philo->rf) = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	*(philo->lf) = 0;
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}