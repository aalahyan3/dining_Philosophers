/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:33:52 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 13:41:30 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TAKEN_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data
{
int					nb_philo;
long				time_to_die;
long				time_to_eat;
long				time_to_sleep;
int					nb_must_eat;
long long			curr_time;
long long			start_time;
int				stop;
pthread_mutex_t	*forks;
pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	pthread_t		thread;
	int				left_fork_index;
	int				right_fork_index;
	t_data			*data;
	long			last_meal;
}	t_philo;



int	main(int ac, char **av);
int	parse(t_data *data, int ac, char **av);
void	start_simulation(t_data *data);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
long long	get_time(void);
void	print_log(t_philo *philo, char *message);

#endif