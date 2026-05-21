/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:54:46 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/21 15:50:03 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  get the length of a string to use in main()*/
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*  destroy all mutexes of forks*/
static void	destroy_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo[0].num_of_philos)
		pthread_mutex_destroy(&info->forks[i]);
}

/*  free all alocated memory and mutexes */
void	freeall(t_info *info)
{
	if (info->forks)
	{
		destroy_mutexes(info);
		free(info->forks);
	}
	free(info->philo);
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->dead_lock);
}

/*  Testing nr of args (5 or 6) and len of each arg
	(arg > 99999 is rejected)  */
int	main(int ac, char **av)
{
	t_info	data;
	int		i;

	data.philo = NULL;
	data.forks = NULL;
	data.dead_flag = 0;
	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (ft_strlen(av[i]) >= 6)
			return (1);
		i++;
	}
	if (var_init(&data, &av[1]) == 1)
	{
		free(data.forks);
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	freeall(&data);
	return (0);
}
