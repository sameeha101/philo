/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:41:40 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/08/28 14:47:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char	*str)
{
	long	res;
	int		flag;

	flag = 1;
	res = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while(*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int) (res * flag));
}
size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error timing\n", 14);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t miliseconds, t_philo *philo)
{
	size_t	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < miliseconds)
	{
		if (!check_if_death(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

void	printing(t_philo *philo, char *str)
{
	if (check_da_ending(philo))
		return ;
	pthread_mutex_lock(&philo->share->write_lock);
	printf("%lu %d %s\n", current_time() - philo->share->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->share->write_lock);
}