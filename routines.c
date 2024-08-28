/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:37:27 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 16:13:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	while (!check_da_ending(philo) && (philo->meals < philo->share->meals_r || philo->share->meals_r == -1))
	{
	// printf("%d %d\n", philo->meals, philo->share->meals_r);
		eating(philo);
		// if(check_da_meals(philo))
		// {
		// 	dropping_forks(philo);
		// 	return (NULL);
		// }
		sleeping(philo);
		thinking(philo);
		
	}
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
	thinking(philo);
	if (philo->id % 2 == 0 && philo->meals == 0)
	{
		ft_usleep(philo->share->to_eat / 2, philo);
	}
	// printf("Test1 %d\n", philo->id);
	check_da_forks(philo);
	// printf("Test2 %d\n", philo->id);
	taking_forks(philo);
	if (!check_da_ending(philo))
		printing(philo, "is eating\n");
	ft_usleep(philo->share->to_eat, philo);
	philo->meals++;
	return (0);
}

void	threading(t_philo *philo, t_share *share)
{
	int			i;
	// pthread_t	monitor;

	i = -1;
	while (++i < share->num_philos)
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
	// pthread_create(&monitor, NULL, monitoring, philo);
	i = -1;
	while (++i < share->num_philos)
		pthread_join(philo[i].philo, NULL);
	// pthread_join(monitor, NULL);
}
