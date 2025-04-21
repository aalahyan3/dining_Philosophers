/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_semulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:26 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 16:15:37 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!philos)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal = get_time();
		philos[i].nb_eat = 0;
		philos[i].pid = fork();
		if (philos[i].pid < 0)
		{
			sem_wait(data->stop_sem);
			data->stop = 1;
			sem_post(data->stop_sem);
			free(philos);
			return ;
		}
		if (philos[i].pid == 0)
			run_philo_child(&philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
		waitpid(philos[i++].pid, NULL, 0);
	free(philos);
}
