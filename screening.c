/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:12:55 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/19 14:47:42 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setting_da_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->ending);
	*(philo->dead_flag) = 1;
	pthread_mutex_unlock(&philo->share->ending);
	pthread_mutex_lock(&philo->share->printed);
	if (philo->share->print_dead == 0)
	{
		pthread_mutex_lock(&philo->share->write_lock);
		printf("%ld %d died\n",
			current_time() - philo->share->start_time, philo->id);
		pthread_mutex_unlock(&philo->share->write_lock);
		philo->share->print_dead = 1;
	}
	pthread_mutex_unlock(&philo->share->printed);
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
