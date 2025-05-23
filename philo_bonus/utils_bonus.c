/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:19:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/30 10:16:12 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_putstr_err(char *err)
{
	write(2, "Error: ", 7);
	while (*err)
		write(2, err++, 1);
	write(2, "\n", 1);
}

void	print_log(t_philo *philo, char *message)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	sem_wait(philo->data->print_sem);
	printf("%lld %d %s\n", time, philo->id, message);
	sem_post(philo->data->print_sem);
}

void	print_death_log(t_philo *philo)
{
	long long	time;

	time = get_time();
	sem_wait(philo->data->print_sem);
	printf("%lld %d %s\n", time - philo->data->start_time, philo->id, DIED);
	sem_post(philo->data->stop_sem);
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->waiter_sem);
	sem_close(philo->meal_sem);
	sem_close(philo->data->stop_sem);
	sem_close(philo->data->print_sem);
	exit(0);
}

void	ft_usleep(t_philo *philo, long long duration)
{
	long long	start;

	(void)philo;
	start = get_time();
	while ((get_time() - start) < duration)
	{
		usleep(500);
	}
}
