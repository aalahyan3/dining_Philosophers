/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:59 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/19 20:24:06 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// int	is_stop_condition(t_philo *philos)
// {
// 	int			i;
// 	int			eat;
// 	long long	curr;
// 	long long	last_meal;
// 	t_data		*data;
// 	int	times_eat;

// 	i = 0;
// 	eat = 0;
// 	data = philos[0].data;
// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_mutex_lock(&data->meal_mutex);
// 		last_meal = philos[i].last_meal;
// 		times_eat = philos[i].nb_eat;
// 		pthread_mutex_unlock(&data->meal_mutex);
// 		curr = get_time();
// 		if (curr - last_meal > data->time_to_die)
// 		{
// 			print_log(&philos[i], DIED);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	someone_died(t_philo *philos)
{
	int			i;
	long long	last_meal;
	t_data		*data;

	i = 0;
	data = philos[0].data;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		if (get_time() - last_meal > data->time_to_die)
		{
			print_log(&philos[i], DIED);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_eat_enough(t_philo *philos)
{
	int		i;
	int		eat_enough;
	int		meals;
	t_data	*data;

	i = 0;
	data = philos[i].data;
	eat_enough = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		meals = philos[i].nb_eat;
		pthread_mutex_unlock(&data->meal_mutex);
		if (meals == data->nb_must_eat)
			eat_enough++;
		i++;
	}
	return (eat_enough == data->nb_philo);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (someone_died(philos) || all_eat_enough(philos))
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
