/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:37:31 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/22 18:06:32 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(char *s, int *overflow)
{
	long	res;
	int		digit;

	res = 0;
	while (*s)
	{
		digit = *s - 48;
		if (res > (LONG_MAX - digit) / 10)
		{
			*overflow = 1;
			return (0);
		}
		res = res * 10 + digit;
		s++;
	}
	return (res);
}


static int	all_digits(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*parse(t_data *data, int ac, char **av)
{
	int	overflow;

	if (ac != 5 && ac != 6)
		return ("invalid nb of args");
	if (!all_digits(av + 1))
		return ("non digit argument");
	overflow = 0;
	data->nb_philo = ft_atol(av[1], &overflow);
	data->time_to_die = ft_atol(av[2], &overflow);
	data->time_to_eat = ft_atol(av[3], &overflow);
	data->time_to_sleep = ft_atol(av[4], &overflow);
	if (ac == 6)
		data->nb_must_eat = ft_atol(av[5], &overflow);
	else
		data->nb_must_eat = -1;
	if (overflow)
		return ("argument number is too large");
	return (NULL);
}

