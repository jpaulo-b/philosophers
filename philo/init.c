/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:56:03 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/28 18:15:21 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alone_philo(t_info *info, int *vals);

/*  Allocate memory for the philosophers 'philo[] and forks[]'*/
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

/*  Set up the information for the simulation */
static void	setup_info(t_info *info, int *vals)
{
	info->dead_flag = 0;
	info->philo[0].num_of_philos = vals[0];
	info->philo[0].time_to_die = (size_t)vals[1];
	info->philo[0].time_to_eat = (size_t)vals[2];
	info->philo[0].time_to_sleep = (size_t)vals[3];
	info->philo[0].num_times_to_eat = vals[4];
	info->philo[0].start_time = get_time();
}

/*  Initialize variables for each philosopher*/
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

/*  Read argc/argv and set an array vals[] with the arguments */
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
	if (vals[0] == 1)
	{
		alone_philo(info, vals);
		return (1);
	}
	setup_info(info, vals);
	return (init_philos(info));
}

int	alone_philo(t_info *info, int *vals)
{
	setup_info(info, vals);
	pthread_mutex_init(&info->write_lock, NULL);
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_lock(&info->write_lock);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&info->write_lock);
	usleep(info->philo[0].time_to_die * 1000);
	pthread_mutex_lock(&info->write_lock);
	printf("%lu 1 died\n", info->philo[0].time_to_die);
	pthread_mutex_unlock(&info->write_lock);
	pthread_mutex_lock(&info->dead_lock);
	info->dead_flag = 1;
	pthread_mutex_unlock(&info->dead_lock);
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->dead_lock);
	return (0);
}


/*  Initialize the philosopher threads */
int	philo_init(t_info *info)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	if (info->philo[0].num_of_philos == 1)
		return (1);
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
