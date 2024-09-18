/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:21:04 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/18 18:39:36 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_share	share;
	t_philo	*philo;

	if (!checking(ac, av))
		return (-1);
	if (!pro_initialize(&share, ac, av))
		return (-1);\
	philo = malloc(sizeof(t_philo) * share.num_philos);
	if (!philo)
		return (-1);
	if (!init_philo(philo, &share))
		return (-1);
	threading(philo, &share);
	destroying(&share);
	return (frees(philo, &share));
}
