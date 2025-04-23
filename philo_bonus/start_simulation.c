/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:26 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/23 16:03:06 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philo *philos, t_data *data)
{
	long long	time;
	int			i;

	time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal = time;
		philos[i].nb_eat = 0;
		i++;
	}
}

void	monitor_process(t_philo *philos, t_data *data)
{
	int	i;

	sem_wait(data->stop_sem);
	sem_close(data->stop_sem);
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->waiter_sem);
	i = 0;
	while (i < data->nb_philo)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	free(philos);
	exit(0);
}

void	launch_monitor(t_philo *philos, t_data *data)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid < 0)
	{
		sem_post(data->stop_sem);
		monitor_process(philos, data);
	}
	if (pid == 0)
		monitor_process(philos, data);
	i = 0;
	while (i < data->nb_philo)
		waitpid(philos[i++].pid, NULL, 0);
	sem_post(data->stop_sem);
	waitpid(pid, NULL, 0);
	free(philos);
}

void	run_philosophers(t_philo *philos, t_data *data)
{
	int	i;
	int	pid;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
		{
			while (--i >= 0)
				kill(philos[i].pid, SIGKILL);
			free(philos);
			return ;
		}
		if (philos[i].pid == 0)
			run_philo_child(&philos[i]);
		i++;
	}
	launch_monitor(philos, data);
}

void	start_simulation(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philos)
		return ;
	i = 0;
	init_philos(philos, data);
	printf("--------------------------------------------------------------\n");
	printf("| %-10s | %-3s | %-40s|\n", "time (ms)", "id", "logs");
	run_philosophers(philos, data);
}
