/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:47:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 14:09:43 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	stop;
	int	meals_had;

	pthread_mutex_lock(&philo->meal_mutex);
	meals_had = philo->nb_eat;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (meals_had == philo->data->nb_must_eat)
		return (1);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (stop);
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
		usleep(100);
	}
	return ;
}

void	print_log(t_philo *philo, char *message)
{
	long long	time;

	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("--------------------------------------------------------------\n");
	printf("| %-10lld | %-3d | %-40s|\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

void	take_forks(t_philo *philo)
{
	if (philo->left_fork_index < philo->right_fork_index)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_index]);
		print_log(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_index]);
		print_log(philo, TAKEN_FORK);
		return ;
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_index]);
		print_log(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_index]);
		print_log(philo, TAKEN_FORK);
		return ;
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_index]);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	print_log(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_index]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_index]);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	print_log(philo, SLEEPING);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void *one_philo_case(t_philo *philo)
{
	print_log(philo, TAKEN_FORK);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(0 + (!(philo->id % 2) * 1000));
	if (philo->data->nb_philo == 1)
		return (one_philo_case(philo));
	while (!should_stop(philo))
	{
		eat(philo);
		print_log(philo, THINKING);
	}
	return (NULL);
}