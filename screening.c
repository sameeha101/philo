/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:12:55 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 15:00:19 by marvin           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->share->ending);
	*(philo->dead_flag) = 1;
	pthread_mutex_unlock(&philo->share->ending);
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

// void	*monitoring(void *p)
// {
// 	int		i;
// 	int		j;
// 	t_philo *philo;
	
// 	philo = (t_philo *)p;
// 	while (1)
// 	{
// 		i = -1;
// 		j = 0;
// 		while (++i < philo->share->num_philos)
// 		{
// 			philo = &philo[i];
// 			if (check_if_death(philo))
// 				break ;
// 			if (philo->share->meals_r != 1 && check_da_meals(philo))
// 				j++;
// 		}
// 		if (philo->share->meals_r != -1 && j == philo->share->num_philos)
// 			setting_da_end(philo);
// 		if (check_da_ending(philo))
// 			break ;
// 	}
// 	return (NULL);
// }