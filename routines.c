/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:37:27 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/18 18:40:18 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	// printf("Im here, %zu\n", current_time() - philo->share->start_time);
	while (!check_da_ending(philo) && (philo->meals < philo->share->meals_r
		|| philo->share->meals_r == -1))
	{
		// pthread_mutex_lock(&philo->share->write_lock);
		// printf("Start of %d\n", philo->id);
		// pthread_mutex_unlock(&philo->share->write_lock);
	// printf("%d %d\n", philo->meals, philo->share->meals_r);
		eating(philo);
		// if(check_da_meals(philo))
		// {
		// 	dropping_forks(philo);
		// 	return (NULL);
		// }
		sleeping(philo);
		thinking(philo);
		// pthread_mutex_lock(&philo->share->write_lock);
		// printf("End of %d\n", philo->id);
		// pthread_mutex_unlock(&philo->share->write_lock);
	}
	// if (philo->meals >= philo->share->meals_r)
	// 	{pthread_mutex_lock(&philo->share->write_lock);
	// 	printf("MEALS DONE: %d\n", philo->id);
	// 	pthread_mutex_unlock(&philo->share->write_lock);}
	// else
	// 	{pthread_mutex_lock(&philo->share->write_lock);
	// 	printf("I DIED!!! %d\n", philo->id);
	// 	pthread_mutex_unlock(&philo->share->write_lock);}
	return (NULL);
}

int	thinking(t_philo *philo)
{
	if (!check_da_ending(philo))
		printing(philo, "is thinking\n");
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (!check_da_ending(philo))
		printing(philo, "is sleeping\n");
	dropping_forks(philo);
	ft_usleep(philo->share->to_sleep, philo);
	return (0);
}

int	eating(t_philo *philo)
{
	// thinking(philo);
	if (philo->id % 2 == 0 && philo->meals == 0)
	{
		ft_usleep(philo->share->to_eat / 2, philo);
	}
	check_da_forks(philo);
	taking_forks(philo);
	if (!check_da_ending(philo))
	{
		printing(philo, "is eating\n");
		ft_usleep(philo->share->to_eat, philo);
		philo->meals++;
		philo->last_meal = current_time();
	}
	return (0);
}

void	threading(t_philo *philo, t_share *share)
{
	int			i;

	i = -1;
	while (++i < share->num_philos)
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
	i = -1;
	while (++i < share->num_philos)
		pthread_join(philo[i].philo, NULL);
}
