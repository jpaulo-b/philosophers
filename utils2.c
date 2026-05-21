/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:20:00 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/21 10:06:41 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_info *info, int philos)
{
	int	i;

	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (1);
	i = -1;
	while (++i < philos)
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork");
}

void	eat_and_release(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_action(philo, "is eating");
	smart_sleep(philo->time_to_eat, philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	count_satisfied(t_info *info)
{
	int	i;
	int	full_count;

	full_count = 0;
	i = -1;
	while (++i < info->philo[0].num_of_philos)
	{
		pthread_mutex_lock(info->philo[i].meal_lock);
		if (info->philo[i].num_times_to_eat > 0
			&& info->philo[i].meals_eaten
			>= info->philo[i].num_times_to_eat)
			full_count++;
		pthread_mutex_unlock(info->philo[i].meal_lock);
	}
	return (full_count);
}

int	check_death(t_info *info)
{
	int		i;
	size_t	now;

	i = -1;
	while (++i < info->philo[0].num_of_philos)
	{
		pthread_mutex_lock(info->philo[i].meal_lock);
		now = get_time();
		if (now - info->philo[i].last_meal
			> info->philo[i].time_to_die)
		{
			print_death(&info->philo[i]);
			pthread_mutex_unlock(info->philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(info->philo[i].meal_lock);
	}
	return (0);
}
