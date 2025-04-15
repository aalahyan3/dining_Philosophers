/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:37:31 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/14 16:45:49 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *s)
{
	long	res;

	res = 0;
	while (*s)
	{
		res = res * 10 + (*s - 48);
		s++;
	}
	return (res);
}

int	parse(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("error ac = %d\n", ac), 0);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	return (1);
}