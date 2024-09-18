/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:12:53 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/09/05 20:40:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_share
{
	int				num_philos;
	int				died;
	int				meals_r;
	int				*fork;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	starting;
	pthread_mutex_t	ending;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks_mu;
}	t_share;

typedef struct s_philo
{
	int				id;
	int				*dead_flag;
	int				*rf;
	int				*lf;
	int				meals;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_share			*share;
	pthread_t		philo;
}	t_philo;

int		ft_strlen(char *str);
int		ft_atoi(char	*str);
int		number(int ac, char **av);
int		checking(int ac, char **av);
void	destroying(t_share *share);
int		pro_initialize(t_share *share, int ac, char **av);
int		init_philo(t_philo *philo, t_share *share);
int		frees(t_philo *philo, t_share *share);
void	*routine(void *p);
int		thinking(t_philo *philo);
int		sleeping(t_philo *philo);
int		eating(t_philo *philo);
size_t	current_time(void);
int		ft_usleep(size_t miliseconds, t_philo *philo);
void	printing(t_philo *philo, char *str);
void	threading(t_philo *philo, t_share *share);
int		check_left(t_philo *philo);
int		check_right(t_philo *philo);
int		check_da_meals(t_philo *philo);
int		check_da_forks(t_philo *philo);
int		take_rf(t_philo *philo);
int		take_lf(t_philo *philo);
int		taking_forks(t_philo *philo);
int		dropping_forks(t_philo *philo);
int		check_da_time(t_philo *philo, t_share *share);
int		setting_da_end(t_philo *philo);
int		check_da_ending(t_philo *philo);
int		check_if_death(t_philo *philo);
void	*monitoring(void *p);

#endif