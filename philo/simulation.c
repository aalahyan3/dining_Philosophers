/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:15:21 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/28 14:11:23 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death_log(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%lld %d %s\n", time, philo->id, DIED);
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print);
	return ;
}

static int	get_left_fork(int id, int nb_p)
{
	if (id == 1)
		return (nb_p - 1);
	else
		return (id - 2);
}

static int	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philos[i].meal_mutex);
			return (0);
		}
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal = get_time();
		philos[i].left_fork_index = get_left_fork(i + 1, data->nb_philo);
		philos[i].right_fork_index = i;
		philos[i].nb_eat = 0;
		i++;
	}
	return (1);
}

static void	start_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			set_stop(data);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos))
	{
		set_stop(data);
		return ;
	}
	i = 0;
	pthread_join(monitor, NULL);
	while (i < data->nb_philo)
		pthread_join(philos[i++].thread, NULL);
}

void	start_simulation(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!philos)
		return ;
	if (!init_philos(philos, data))
	{
		free(philos);
		return ;
	}
	data->start_time = get_time();
	start_threads(philos, data);
	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&philos[i++].meal_mutex);
	free(philos);
}
