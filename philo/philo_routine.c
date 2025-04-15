/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:47:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 15:20:25 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_log(t_philo *philo, char *message)
{
	long long time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time;
	printf("--------------------------------------------------------------\n");
	printf("| %-10lld | %-3d | %-40s|\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->forks[philo->left_fork_index]);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
		return ;
	}
	print_log(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_index]);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_index]);
		return ;
	}

	print_log(philo, TAKEN_FORK);

	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_index]);
		return ;
	}
	philo->last_meal = get_time() - philo->data->start_time;
	print_log(philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_index]);

	if (philo->data->stop)
		return ;
	print_log(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(1000 + (philo->id % 2 * 1000));
	while (!philo->data->stop)
	{
		print_log(philo, THINKING);
		eat(philo);
	}
	return (NULL);
}