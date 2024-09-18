/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:32:56 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/05 19:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_init(t_share *share)
{
	int	i;

	i = -1;
	pthread_mutex_init(&share->meal_lock, NULL);
	pthread_mutex_init(&share->write_lock, NULL);
	pthread_mutex_init(&share->starting, NULL);
	pthread_mutex_init(&share->ending, NULL);
	while (++i < share->num_philos)
		pthread_mutex_init(&share->forks_mu[i], NULL);
}

int	pro_initialize(t_share *share, int ac, char **av)
{
	int	i;

	i = -1;
	share->died = 0;
	share->num_philos = ft_atoi(av[1]);
	share->to_die = ft_atoi(av[2]);
	share->to_eat = ft_atoi(av[3]);
	share->to_sleep = ft_atoi(av[4]);
	share->forks_mu = malloc(sizeof(pthread_mutex_t) * share->num_philos);
	if (!share->forks_mu)
		return (0);
	share->fork = malloc(sizeof(int) * share->num_philos);
	if (!share->fork)
		return (0);
	while (++i < share->num_philos)
		share->fork[i] = 0;
	if (ac == 6)
		share->meals_r = ft_atoi(av[5]);
	else
		share->meals_r = -1;
	mutex_init(share);
	share->start_time = current_time();
	return (1);
}

int	init_philo(t_philo *philo, t_share *share)
{
	int	i;

	i = 0;
	while (i < share->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].dead_flag = &share->died;
		philo[i].meals = 0;
		philo[i].last_meal = current_time();
		philo[i].share = share;
		philo[i].l_fork = &share->forks_mu[i];
		if (i == share->num_philos - 1)
			philo[i].r_fork = &share->forks_mu[0];
		else
			philo[i].r_fork = &share->forks_mu[i + 1];
		philo[i].lf = &share->fork[i];
		if (i == share->num_philos - 1)
			philo[i].rf = &share->fork[0];
		else
			philo[i].rf = &share->fork[i + 1];
		// if (philo[i].id == 0)
		// 	philo[i].lf = &share->fork[share->num_philos - 1];
		// else
		// 	philo[i].lf = &share->fork[philo[i].id - 1];
		i++;
	}
	return (1);
}
