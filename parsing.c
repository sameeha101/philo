/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:19:17 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 14:28:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = -1;
		if (av[i][0] == '-' || (av[i][0] == '+'))
			j++;
		while (av[i][++j])
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
		i++;
	}
	return (1);
}

int	checking(int ac, char **av)
{
	if ((ac < 5) || (ac > 6) || !(number(ac, av)))
		return (write(2, "Incorrect parameters!\n", 23));
	if ((ft_atoi(av[1]) < 1) || (ft_atoi(av[1]) > 200))
		return (write(2, "Use between 1 - 200 philos\n", 28));
	if ((ft_atoi(av[2]) < 1) || (ft_atoi(av[2]) > INT_MAX))
		return (write(2, "Use numbers within range\n", 26));
	if ((ft_atoi(av[3]) < 1) || (ft_atoi(av[3]) > INT_MAX))
		return (write(2, "Use numbers within range\n", 26));
	if ((ft_atoi(av[4]) < 1) || (ft_atoi(av[4]) > INT_MAX))
		return (write(2, "Use numbers within range\n", 26));
	if (ac == 6)
		if ((ft_atoi(av[5]) < 1) || (ft_atoi(av[5]) > INT_MAX))
			return (write(2, "Use numbers within range\n", 26));
	return (1);
}

