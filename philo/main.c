/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/23 15:19:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes_1(t_data *data)
{
	data->start_time = get_time();
	data->stop = 0;
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print);
		return (0);
	}
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->stop_mutex);
		return (0);
	}
	return (1);
}

static int	init_data(t_data *data)
{
	int	i;
	int	j;

	if (!init_mutexes_1(data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			j = 0;
			pthread_mutex_destroy(&data->print);
			pthread_mutex_destroy(&data->stop_mutex);
			while (j < i)
				pthread_mutex_destroy(&data->forks[j++]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print);
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*parse_res;

	parse_res = parse(&data, ac, av);
	if (parse_res)
	{
		ft_putstr_err(parse_res);
		return (1);
	}
	if (!init_data(&data))
		return (2);
	start_simulation(&data);
	cleanup(&data);
}
