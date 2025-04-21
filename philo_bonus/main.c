/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:18:03 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 21:54:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"



int	init_data(t_data *data)
{
	sem_unlink(STOP_SEMAPHORE);
	sem_unlink(FORKS_SEMAPHORE);
	sem_unlink(PRINT_SEMAPHORE);
	data->forks_sem = sem_open(FORKS_SEMAPHORE, O_CREAT | O_EXCL, 0644, data->nb_philo);
	if (data->forks_sem == SEM_FAILED)
		return (0);
	data->print_sem = sem_open(PRINT_SEMAPHORE, O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
	{
		sem_close(data->forks_sem);
		sem_unlink(FORKS_SEMAPHORE);
		return (0);
	}
	data->stop_sem = sem_open(STOP_SEMAPHORE, O_CREAT | O_EXCL, 0644, 0);
	if (data->stop_sem == SEM_FAILED)
	{
		sem_close(data->forks_sem);
		sem_close(data->print_sem);
		sem_unlink(PRINT_SEMAPHORE);
		sem_unlink(FORKS_SEMAPHORE);
		return (0);
	}
	data->start_time = get_time();
	return (1);
}

int	main(int ac, char **av)
{
	char	*parse_res;
	t_data	data;

	parse_res = parse(&data, ac, av);
	if (parse_res)
	{
		ft_putstr_err(parse_res);
		return (1);
	}
	if (!init_data(&data))
		return (1);
	start_simulation(&data);
}