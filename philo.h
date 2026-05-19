/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-b <jpaulo-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:55:17 by jpaulo-b          #+#    #+#             */
/*   Updated: 2026/05/19 16:17:43 by jpaulo-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
} 	t_philo;

typedef struct s_info
{
	int			dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
} 	t_info;

int		var_init(t_info *info, char **av);
int		philo_init(t_info *info);
size_t	get_time(void);
void	smart_sleep(size_t time, t_philo *philo);
int		all_meals_done(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat_and_release(t_philo *philo);
int		count_satisfied(t_info *info);
int		check_death(t_info *info);
int		is_dead(t_philo *philo);
void	set_dead(t_philo *philo);
int		print_action(t_philo *philo, char *action);
int		print_death(t_philo *philo);
int		ft_atoi(const char *str);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

#endif
