/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:56:03 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/19 15:59:03 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_info *info)
{
	int i;

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
		info->philo[i].l_fork = &info->forks[i];
		info->philo[i].r_fork = &info->forks[(i + 1) % info->philo[0].num_of_philos];
		info->philo[i].write_lock = &info->write_lock;
		info->philo[i].dead_lock = &info->dead_lock;
		info->philo[i].meal_lock = &info->meal_lock;
	}
	return (0);
}

int	var_init(t_info *info, char **av)
{
	int	philos;
	int	tdie;
	int	teat;
	int	sleep;
	int	eat_count;
	int	i;

	philos = ft_atoi(av[0]);
	tdie = ft_atoi(av[1]);
	teat = ft_atoi(av[2]);
	sleep = ft_atoi(av[3]);
	eat_count = av[4] ? ft_atoi(av[4]) : 0;
	if (philos < 1 || tdie < 1 || teat < 1 || sleep < 1 || (av[4] && eat_count < 1))
		return (1);
	info->philo = malloc(sizeof(t_philo) * philos);
	if (!info->philo)
		return (1);
	info->forks = malloc(sizeof(pthread_mutex_t) * philos);
	if (!info->forks)
		return (1);
	if (pthread_mutex_init(&info->write_lock, NULL) != 0
		|| pthread_mutex_init(&info->meal_lock, NULL) != 0
		|| pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (1);
	i = -1;
	while (++i < philos)
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
	info->dead_flag = 0;
	info->philo[0].num_of_philos = philos;
	info->philo[0].num_times_to_eat = eat_count;
	info->philo[0].time_to_die = (size_t)tdie;
	info->philo[0].time_to_eat = (size_t)teat;
	info->philo[0].time_to_sleep = (size_t)sleep;
	info->philo[0].start_time = get_time();
	if (init_philos(info) != 0)
		return (1);
	return (0);
}

int	philo_init(t_info *info)
{
	int		i;
	pthread_t	monitor;

	i = -1;
	while (++i < info->philo[0].num_of_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL,
			philosopher_routine, &info->philo[i]) != 0)
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
