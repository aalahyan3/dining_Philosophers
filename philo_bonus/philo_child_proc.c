/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:28:15 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/22 14:42:00 by aalahyan         ###   ########.fr       */
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
	print_log(philo, EATING);
	philo->last_meal = get_time();
	philo->nb_eat += 1;
	ft_usleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	print_log(philo, SLEEPING);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	one_philo_case(t_philo *philo)
{
	print_log(philo, TAKEN_FORK);
	ft_usleep(philo, philo->data->time_to_die);
	print_log(philo, DIED);
	sem_post(philo->data->stop_sem);
	exit(0);
}

void	run_philo_child(t_philo *philo)
{
	long long time;


	if (philo->data->nb_philo == 1)
		one_philo_case(philo);
	while (1)
	{
		if (philo->data->nb_must_eat != -1 && philo->nb_eat == philo->data->nb_must_eat)
			break ;
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			time = get_time() - philo->data->start_time;
			sem_wait(philo->data->print_sem);
			printf("--------------------------------------------------------------\n");
			printf("| %-10lld | %-3d | %-40s|\n", time, philo->id, DIED);
			sem_post(philo->data->stop_sem);
			break ;
		}
		eat_philo(philo);
		print_log(philo, THINKING);
	}
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->meal_sem);
	exit(0);
}
