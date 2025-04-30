/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:42:57 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/30 17:29:56 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_err(char *err)
{
	write(2, "Error: ", 7);
	while (*err)
		write(2, err++, 1);
	write(2, "\n", 1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep( t_philo *philo, long long time)
{
	long long	start;
	int			stop;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		stop = philo->data->stop;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (stop)
			return ;
		usleep(500);
	}
	return ;
}

void	print_log(t_philo *philo, char *message)
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
	printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
