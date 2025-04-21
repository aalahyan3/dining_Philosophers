/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:19:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 19:34:51 by aalahyan         ###   ########.fr       */
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
	sem_wait(philo->data->stop_sem);
	if (philo->data->stop)
	{
		sem_post(philo->data->stop_sem);
		sem_post(philo->data->print_sem);
		return ;
	}
	sem_post(philo->data->stop_sem);
	printf("--------------------------------------------------------------\n");
	printf("| %-10lld | %-3d | %-40s|\n", time, philo->id, message);
	sem_post(philo->data->print_sem);
}

void	ft_usleep( t_philo *philo, long long time)
{
	long long	start;
	int			stop;

	start = get_time();
	while ((get_time() - start) < time)
	{
		sem_wait(philo->data->stop_sem);
		stop = philo->data->stop;
		sem_post(philo->data->stop_sem);
		if (stop)
			return ;
		usleep(100);
	}
	return ;
}

