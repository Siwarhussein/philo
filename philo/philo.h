/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:17:16 by siwhusse          #+#    #+#             */
/*   Updated: 2026/02/15 22:32:56 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		init_data(t_data *data);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
long	get_time(void);
int		pars_args(t_data *data, int argc, char **argv);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
void	cleanup(t_data *data);
int		print_state(t_philo *philo, char *state);
int		check_stop(t_data *data);
void	precise_sleep(long usec, t_philo *philo);
void	set_stop(t_data *data);
void	check_philo_death(t_data *data, int i, long now);
void	check_routine(t_philo *philo, t_data *data);
void	check_which_first(t_philo *philo);

#endif
