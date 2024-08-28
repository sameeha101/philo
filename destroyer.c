/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:05:41 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/24 13:42:41 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroying(t_share *share)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&share->meal_lock);
	pthread_mutex_destroy(&share->write_lock);
	pthread_mutex_destroy(&share->starting);
	pthread_mutex_destroy(&share->ending);
	while (++i < share->num_philos)
		pthread_mutex_destroy(&share->forks_mu[i]);
}

int	frees(t_philo *philo, t_share *share)
{
	if (share->fork)
		free(share->fork);
	if (share->forks_mu)
		free(share->forks_mu);
	if (philo)
		free(philo);
	return (0);
}
