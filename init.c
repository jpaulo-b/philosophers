/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:56:03 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/21 09:58:24 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_philo(t_info *info, int philos)
{
	info->philo = malloc(sizeof(t_philo) * philos);
	if (!info->philo)
		return (1);
	info->forks = malloc(sizeof(pthread_mutex_t) * philos);
	if (!info->forks)
		return (1);
	return (0);
}

static void	setup_info(t_info *info, int *vals)
{
	info->dead_flag = 0;
	info->philo[0].num_of_philos = vals[0];
	info->philo[0].num_times_to_eat = vals[4];
	info->philo[0].time_to_die = (size_t)vals[1];
	info->philo[0].time_to_eat = (size_t)vals[2];
	info->philo[0].time_to_sleep = (size_t)vals[3];
	info->philo[0].start_time = get_time();
}

static int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo[0].num_of_philos)
	{
		info->philo[i].id = i + 1;
		info->philo[i].eating = 0;
		info->philo[i].meals_eaten = 0;
		info->philo[i].num_of_philos = info->philo[0].num_of_philos;
		info->philo[i].num_times_to_eat = info->philo[0].num_times_to_eat;
		info->philo[i].dead = &info->dead_flag;
		info->philo[i].time_to_die = info->philo[0].time_to_die;
		info->philo[i].time_to_eat = info->philo[0].time_to_eat;
		info->philo[i].time_to_sleep = info->philo[0].time_to_sleep;
		info->philo[i].start_time = info->philo[0].start_time;
		info->philo[i].last_meal = info->philo[0].start_time;
		info->philo[i].l_fork = &info->forks[i];
		info->philo[i].r_fork = &info->forks[
			(i + 1) % info->philo[0].num_of_philos];
		info->philo[i].write_lock = &info->write_lock;
		info->philo[i].dead_lock = &info->dead_lock;
		info->philo[i].meal_lock = &info->meal_lock;
	}
	return (0);
}

int	var_init(t_info *info, char **av)
{
	int	vals[5];

	vals[0] = ft_atoi(av[0]);
	vals[1] = ft_atoi(av[1]);
	vals[2] = ft_atoi(av[2]);
	vals[3] = ft_atoi(av[3]);
	vals[4] = 0;
	if (av[4])
		vals[4] = ft_atoi(av[4]);
	if (vals[0] < 1 || vals[1] < 1 || vals[2] < 1 || vals[3] < 1)
		return (1);
	if (av[4] && vals[4] < 1)
		return (1);
	if (malloc_philo(info, vals[0]) != 0)
		return (1);
	if (init_mutexes(info, vals[0]) != 0)
		return (1);
	setup_info(info, vals);
	return (init_philos(info));
}

int	philo_init(t_info *info)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < info->philo[0].num_of_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL,
				philosopher_routine, (void *)&info->philo[i]) != 0)
			return (1);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, info) != 0)
		return (1);
	i = -1;
	while (++i < info->philo[0].num_of_philos)
		pthread_join(info->philo[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
