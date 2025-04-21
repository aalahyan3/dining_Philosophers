/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:18:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/21 20:49:12 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# define FORKS_SEMAPHORE	"/tmp/forks"
# define PRINT_SEMAPHORE	"/tmp/print"
# define STOP_SEMAPHORE		"/tmp/stop"
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
	long long			start_time;
	sem_t				*forks_sem;
	sem_t				*print_sem;
	sem_t				*stop_sem;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				pid;
	int				nb_eat;
	pthread_t		monitor;
	t_data			*data;
	long long		last_meal;
	sem_t			*meal_sem;
}	t_philo;

int		main(int ac, char **av);
char	*parse(t_data *data, int ac, char **av);
long long	get_time(void);
void	ft_putstr_err(char *err);
void	run_philo_child(t_philo *philo);
void	print_log(t_philo *philo, char *message);
void	ft_usleep( t_philo *philo, long long time);
char	*get_unique_sem_name(int id);
void	start_simulation(t_data *data);
char	*get_unique_sem_name(int id);

#endif