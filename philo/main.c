/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 15:15:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	int	i;
	int	j;

	data->curr_time = 0;
	data->start_time = get_time();
	data->stop = 0;

	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->print);
		return (0);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			j = 0;
			pthread_mutex_destroy(&data->print);
			while (j < i)
				pthread_mutex_destroy(&data->forks[j++]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse(&data, ac, av))
		return (1);
	if (!init_data(&data))
		return (2);
	start_simulation(&data);
}