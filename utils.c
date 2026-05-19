/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:56:41 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/19 17:57:00 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	number;

	number = 0;
	if (*str == '\0')
		return (-1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		number = number * 10 + (*str - '0');
		if (number > 2147483647)
			return (-1);
		str++;
	}
	if (number <= 0)
		return (-1);
	return ((int)number);
}

size_t	get_time(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (0);
	return ((size_t)current.tv_sec * 1000ull + (size_t)current.tv_usec / 1000ull);
}

void	smart_sleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (!is_dead(philo))
	{
		if (get_time() - start >= time)
			break ;
		usleep(250);
	}
}

int	all_meals_done(t_philo *philo)
{
	if (philo->num_times_to_eat > 0
		&& philo->meals_eaten >= philo->num_times_to_eat)
		return (1);
	return (0);
}
