/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:28:15 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/29 21:39:14 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_philo(t_philo *philo)
{
	sem_wait(philo->data->waiter_sem);
	sem_wait(philo->data->forks_sem);
	print_log(philo, TAKEN_FORK);
	sem_wait(philo->data->forks_sem);
	print_log(philo, TAKEN_FORK);
	sem_post(philo->data->waiter_sem);
	sem_wait(philo->meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->meal_sem);
	print_log(philo, EATING);
	ft_usleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	sem_wait(philo->meal_sem);
	philo->nb_eat += 1;
	sem_post(philo->meal_sem);
	print_log(philo, SLEEPING);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	one_philo_case(t_philo *philo)
{
	print_log(philo, TAKEN_FORK);
	ft_usleep(philo, philo->data->time_to_die);
	print_log(philo, DIED);
	sem_close(philo->meal_sem);
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->data->stop_sem);
	sem_close(philo->data->waiter_sem);
	sem_post(philo->data->stop_sem);
	exit(0);
}

void	*monitor_routine(void *arg)
{ 
	t_philo		*philo;
	long long	last_meal;
	int			meals;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->meal_sem);
		last_meal = philo->last_meal;
		meals = philo->nb_eat;
		sem_post(philo->meal_sem);
		if (get_time() - last_meal >= philo->data->time_to_die)
			return (print_death_log(philo), NULL);
		else if (meals == philo->data->nb_must_eat)
			philo_ate_enough(philo);
		if (philo->data->nb_philo % 2 == 0)
			usleep(500);
		else
			usleep(50);
	}
	return (NULL);
}

void	start_thread(t_philo *philo)
{
	char	*uniq_sem;

	uniq_sem = get_unique_sem_name(philo->id);
	sem_unlink(uniq_sem);
	philo->meal_sem = sem_open(uniq_sem, O_CREAT | O_EXCL, 0644, 1);
	if (philo->meal_sem == SEM_FAILED)
	{
		free(uniq_sem);
		sem_close(philo->data->forks_sem);
		sem_close(philo->data->print_sem);
		sem_close(philo->data->stop_sem);
		sem_close(philo->data->waiter_sem);
		exit(1);
	}
	sem_unlink(uniq_sem);
	free(uniq_sem);
	if (pthread_create(&philo->monitor, NULL, monitor_routine, philo))
	{
		sem_close(philo->data->forks_sem);
		sem_close(philo->data->print_sem);
		sem_close(philo->data->stop_sem);
		sem_close(philo->data->waiter_sem);
		sem_close(philo->meal_sem);
		exit(1);
	}
	usleep(100);
}

void	run_philo_child(t_philo *philo)
{
	philo->last_meal = get_time();
	start_thread(philo);
	if (philo->data->nb_philo == 1)
		one_philo_case(philo);
	while (1)
	{
		eat_philo(philo);
		print_log(philo, THINKING);
	}
	pthread_join(philo->monitor, NULL);
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->meal_sem);
	exit(0);
}
