/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:37:27 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/19 14:46:42 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!check_da_ending(philo) && (philo->meals < philo->share->meals_r
			|| philo->share->meals_r == -1))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	thinking(t_philo *philo)
{
	printing(philo, "is thinking");
	return (0);
}

int	sleeping(t_philo *philo)
{
	printing(philo, "is sleeping");
	dropping_forks(philo);
	ft_usleep(philo->share->to_sleep, philo);
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->meals == 0)
	{
		ft_usleep(philo->share->to_eat / 2, philo);
	}
	taking_forks(philo);
	if (!check_da_ending(philo) && philo->share->num_philos > 1)
	{
		printing(philo, "is eating");
		ft_usleep(philo->share->to_eat, philo);
		philo->meals++;
		philo->last_meal = current_time();
	}
	return (0);
}

void	threading(t_philo *philo, t_share *share)
{
	int	i;

	i = -1;
	while (++i < share->num_philos)
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
	i = -1;
	while (++i < share->num_philos)
		pthread_join(philo[i].philo, NULL);
}
