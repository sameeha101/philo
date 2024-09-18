/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:12:55 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/05 20:46:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_da_time(t_philo *philo, t_share *share)
{
	pthread_mutex_lock(&philo->share->starting);
	if (current_time() - share->start_time >= philo->share->to_die)
	{
		pthread_mutex_unlock(&philo->share->starting);
		return (1);
	}
	pthread_mutex_unlock(&philo->share->starting);
	return (0);
}

int	setting_da_end(t_philo *philo)
{
	if (check_da_ending(philo))
		return (1);
	pthread_mutex_lock(&philo->share->ending);
	*(philo->dead_flag) = 1;
	pthread_mutex_unlock(&philo->share->ending);
	pthread_mutex_lock(&philo->share->write_lock);
	printf("%ld %d died\n",
		current_time() - philo->share->start_time, philo->id);
	pthread_mutex_unlock(&philo->share->write_lock);
	return (0);
}

int	check_da_ending(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->ending);
	if (*(philo->dead_flag) == 1)
	{
		pthread_mutex_unlock(&philo->share->ending);
		return (1);
	}
	pthread_mutex_unlock(&philo->share->ending);
	return (0);
}

int	check_if_death(t_philo *philo)
{
	if (check_da_ending(philo))
		return (1);
	if (check_da_time(philo, philo->share))
	{
		setting_da_end(philo);
		pthread_mutex_lock(&philo->share->write_lock);
		printing(philo, "died\n");
		pthread_mutex_unlock(&philo->share->write_lock);
		return (1);
	}
	return (0);
}
