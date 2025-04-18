/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:59 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/18 19:37:16 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_stop_condition(t_philo *philos)
{
	int			i;
	int			eat;
	long long	curr;
	long long	last_meal; // added to store last_meal value outside mutex
	t_data		*data; // added to avoid repeated access to philos[0].data

	i = 0;
	eat = 0;
	data = philos[0].data; // assigned once for cleaner code
	// while (data->nb_must_eat >= 0 && i < data->nb_philo)
	// {
	// 	if (philos[i].nb_eat >= data->nb_must_eat)
	// 		eat++;
	// 	i++;
	// }
	// if (data->nb_must_eat >= 0 && eat == data->nb_philo)
	// 	return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = philos[i].last_meal; // moved access to local variable
		pthread_mutex_unlock(&data->meal_mutex); // unlocked before print_log
		curr = get_time();
		if (curr - last_meal > data->time_to_die)
		{
			print_log(&philos[i], DIED); // now called after unlocking meal_mutex
			return (1);
		}
		i++;
	}
	return (0);
}




void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (is_stop_condition(philos))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
