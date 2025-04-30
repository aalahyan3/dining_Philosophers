/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unique_sem_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:08 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/22 17:34:55 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	count_digits(int id)
{
	int	digits;

	digits = 0;
	if (id == 0)
		return (1);
	while (id > 0)
	{
		id /= 10;
		digits++;
	}
	return (digits);
}

char	*get_unique_sem_name(int id)
{
	char	*sem_name;
	int		len;
	int		i;

	len = 3 + count_digits(id);
	sem_name = malloc(len * sizeof(char));
	if (!sem_name)
		return (NULL);
	sem_name[0] = 's';
	sem_name[1] = 'p';
	i = len - 2;
	if (id == 0)
		sem_name[i] = '0';
	while (id > 0)
	{
		sem_name[i] = (id % 10) + '0';
		id /= 10;
		i--;
	}
	sem_name[len - 1] = '\0';
	return (sem_name);
}
