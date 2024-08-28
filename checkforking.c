/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkforking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:53:07 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 16:11:46 by marvin           ###   ########.fr       */
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
	if(*(philo->rf) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}


int	check_da_meals(t_philo *philo)
{
	if (philo->share->meals_r == -1)
		return (0);
	pthread_mutex_lock(&philo->share->meal_lock);
	if (philo->meals >= philo->share->meals_r)
	{
		pthread_mutex_unlock(&philo->share->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->share->meal_lock);
	return (0);
}

int	check_da_forks(t_philo *philo)
{
	// printf("%d, %d, %d\n", philo->id, *philo->rf, *philo->lf);
	while (!check_da_ending(philo))
	{
		if ((check_right(philo) || check_left(philo)) && !check_da_ending(philo))
			ft_usleep(100, philo);
		else
			break ;
	}
	return (0);
}