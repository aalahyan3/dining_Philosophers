/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:28:15 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 19:35:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_philo(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	print_log(philo, TAKEN_FORK);
	sem_wait(philo->data->forks_sem);
	print_log(philo, TAKEN_FORK);
	print_log(philo, EATING);
	sem_wait(philo->meal_sem);
	philo->last_meal = get_time();
	philo->nb_eat += 1;
	sem_post(philo->meal_sem);
	ft_usleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	print_log(philo, SLEEPING);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	*philo_observer(void *arg)
{
	t_philo			*philo;
	long long		last_meal_time;
	int				meals_had;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->meal_sem);
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			sem_post(philo->meal_sem);
			sem_wait(philo->data->stop_sem);
			if (!philo->data->stop)
			{
				philo->data->stop = 1;
				print_log(philo, DIED);
				sem_post(philo->data->stop_sem);
			}
			sem_post(philo->data->stop_sem);
			return (NULL);
		}
		sem_post(philo->meal_sem);
		usleep(1000);
	}
	return (NULL);
}





void	run_philo_child(t_philo *philo)
{
	int	stop;
	char	*unique_sem_name;

	unique_sem_name	= get_unique_sem_name(philo->id);
	if (!unique_sem_name)
	{
		sem_wait(philo->data->stop_sem);
		philo->data->stop = 1;
		sem_post(philo->data->stop_sem);
		sem_close(philo->data->forks_sem);
		sem_close(philo->data->print_sem);
		sem_close(philo->data->stop_sem);
		return ;		
	}
	sem_unlink(unique_sem_name);
	philo->meal_sem = sem_open(unique_sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->meal_sem == SEM_FAILED)
	{
		sem_wait(philo->data->stop_sem);
		philo->data->stop = 1;
		sem_post(philo->data->stop_sem);
		sem_close(philo->data->forks_sem);
		sem_close(philo->data->print_sem);
		sem_close(philo->data->stop_sem);
		free(unique_sem_name);
		return ;

	}
	sem_unlink(unique_sem_name);
	if (pthread_create(&philo->monitor, NULL, philo_observer, philo))
	{
		sem_wait(philo->data->stop_sem);
		philo->data->stop = 1;
		sem_post(philo->data->stop_sem);
		sem_close(philo->data->forks_sem);
		sem_close(philo->data->print_sem);
		sem_close(philo->data->stop_sem);
		sem_close(philo->meal_sem);
		free(unique_sem_name);
		return ;
	}
	while (1)
	{
		sem_wait(philo->data->stop_sem);
		stop = philo->data->stop;
		sem_post(philo->data->stop_sem);
		if (stop)
			break ;
		eat_philo(philo);
		print_log(philo, THINKING);
	}
	pthread_join(philo->monitor, NULL);
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->data->stop_sem);
	free(unique_sem_name);
	exit(0);
}