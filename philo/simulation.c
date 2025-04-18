/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:15:21 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/18 19:19:29 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_left_fork(int id, int nb_p)
{
	// if (id == 1)
	// 	return (nb_p - 1);
	// else
	// 	return (id - 2);
	if (id == 1)
		return (nb_p - 1);
	else
		return (id - 2);
}

int	get_right_fork(int id, int nb_p)
{

	return (id - 1);
}

void	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal = get_time();
		philos[i].left_fork_index = get_left_fork(i + 1, data->nb_philo);
		philos[i].right_fork_index = get_right_fork(i + 1, data->nb_philo);
		philos[i].nb_eat = 0;
		i++;
	}
}

void	start_simulation(t_data *data)
{
	t_philo		*philos;
	pthread_t	monitor;
	int		i;

	philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!philos)
		return ;
	init_philos(philos, data);
	i = 0;
	printf("--------------------------------------------------------------\n");
	printf("| %-10s | %-3s | %-40s|\n", "time (ms)", "id", "logs");
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			data->stop = 1;
			free(philos);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos))
	{
		data->stop = 1;
		free(philos);
		return ;
	}
	i = 0;
	pthread_join(monitor, NULL);
	while (i < data->nb_philo)
		pthread_join(philos[i++].thread, NULL);
	free(philos);
}
