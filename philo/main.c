/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:27:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/19 16:16:30 by aalahyan         ###   ########.fr       */
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
	if (pthread_mutex_init(&data->stop_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->stop_mutex);
		return (0);
	}
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		return (0);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			j = 0;
			pthread_mutex_destroy(&data->print);
			pthread_mutex_destroy(&data->stop_mutex);
			pthread_mutex_destroy(&data->meal_mutex);
			while (j < i)
				pthread_mutex_destroy(&data->forks[j++]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

void cleanup(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	while ( i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

void l()
{
	system("leaks -q philo");
}

void ft_putstr_err(char *err)
{
	write(2, "Error: ", 7);
	while (*err)
		write(2, err++, 1);
	write(2, "\n", 1);
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