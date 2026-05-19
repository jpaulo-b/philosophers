/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:56:34 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/19 16:16:59 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		smart_sleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		take_forks(philo);
		eat_and_release(philo);
		if (all_meals_done(philo))
			break ;
		print_action(philo, "is sleeping");
		smart_sleep(philo->time_to_sleep, philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

static int	philo_satisfied(t_info *info)
{
	int full_count;

	full_count = count_satisfied(info);
	if (info->philo[0].num_times_to_eat > 0
		&& full_count == info->philo[0].num_of_philos)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (check_death(info))
			return (NULL);
		if (philo_satisfied(info))
		{
			set_dead(&info->philo[0]);
			return (NULL);
		}
		if (is_dead(&info->philo[0]))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
