/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:59 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/29 16:34:31 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	someone_died(t_philo *philos)
{
	int			i;
	long long	last_meal;
	t_data		*data;

	i = 0;
	data = philos[0].data;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		last_meal = philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (get_time() - last_meal >= data->time_to_die)
			return (print_death_log(&philos[i]), 1);
		i++;
	}
	return (0);
}

static int	all_eat_enough(t_philo *philos)
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
		pthread_mutex_lock(&philos[i].meal_mutex);
		meals = philos[i].nb_eat;
		pthread_mutex_unlock(&philos[i].meal_mutex);
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
		if (all_eat_enough(philos))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		if (someone_died(philos))
			return (NULL);
		usleep(50);
	}
	return (NULL);
}
