/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:41:16 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/19 14:58:27 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_lfork(t_philo *philo)
{
	int	can_grab;

	can_grab = 0;
	while (!check_da_ending(philo) && !can_grab)
	{
		pthread_mutex_lock(philo->l_fork);
		can_grab = (*philo->lf == 0);
		if (can_grab)
			*philo->lf = 1;
		pthread_mutex_unlock(philo->l_fork);
	}
	if (!check_da_ending(philo))
		printing(philo, "has taken a fork");
	if (!can_grab)
		usleep(100);
}

void	grab_rfork(t_philo *philo)
{
	int	grab_again;

	grab_again = 0;
	while (!check_da_ending(philo) && !grab_again)
	{
		pthread_mutex_lock(philo->r_fork);
		grab_again = (*philo->rf == 0);
		if (grab_again)
			*philo->rf = 1;
		pthread_mutex_unlock(philo->r_fork);
	}
	if (!check_da_ending(philo))
		printing(philo, "has taken a fork");
	if (!grab_again)
		usleep(100);
}

int	taking_forks(t_philo *philo)
{
	grab_lfork(philo);
	if (philo->share->num_philos == 1)
	{
		ft_usleep(philo->share->to_die * 2, philo);
		return (0);
	}
	grab_rfork(philo);
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
