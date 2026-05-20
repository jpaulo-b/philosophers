/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:55:50 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/20 14:04:10 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(philo->dead_lock);
	value = *(philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	return (value);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	*(philo->dead) = 1;
	pthread_mutex_unlock(philo->dead_lock);
}

int	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_lock(philo->write_lock);
	printf("%zu  %d %s\n", get_time() - philo->start_time,
		philo->id, action);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (!*(philo->dead))
	{
		*(philo->dead) = 1;
		pthread_mutex_lock(philo->write_lock);
		printf("%zu  %d died\n", get_time() - philo->start_time,
			philo->id);
		pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}
