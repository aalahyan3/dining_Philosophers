/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:59 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 13:41:58 by aalahyan         ###   ########.fr       */
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

	i = 0;
	eat = 0;
	curr = philos[0].data->curr_time;
	while (philos[0].data->nb_must_eat >= 0 && i < philos[0].data->nb_philo)
	{
		if (philos[i].nb_eat >= philos[i].data->nb_must_eat)
			eat++;
		i++;
	}
	if (philos[0].data->nb_must_eat >= 0 && eat == philos[0].data->nb_philo)
		return (1);
	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		if (curr - philos[i].last_meal > philos[i].data->time_to_die)
		{
			pthread_mutex_lock(&philos[i].data->print);
			print_log(&philos[i], DIED);
			pthread_mutex_unlock(&philos[i].data->print);
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
	data->start_time = get_time();
	while (1)
	{
		if (is_stop_condition(philos))
		{
			data->stop = 1;
			return (NULL);
		}
		data->curr_time = get_time() - data->start_time;
		usleep(1000);
	}
	return (NULL);
}
