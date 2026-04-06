/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:33:33 by siwhusse          #+#    #+#             */
/*   Updated: 2026/04/06 18:54:38 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_sleep(long usec, t_philo *philo)
{
	long	start;
	long	end;

	start = get_time();
	end = start + (usec / 1000);
	while (get_time() < end
		&& !check_stop(philo->data))
		usleep(500);
}

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex); // stop is shared between threads, so we need to lock the mutex to read it safely
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000)
		+ (tv.tv_usec / 1000));
}

void	check_philo_death(t_data *data, int i, long now)
{
	long	time_since_last_meal;
	int		meals_complete;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	time_since_last_meal = now
		- data->philos[i].last_meal_time;
	meals_complete = data->must_eat > 0
		&& data->philos[i].meals_eaten
		>= data->must_eat;
	if (time_since_last_meal > data->time_to_die
		&& !meals_complete)
	{
		pthread_mutex_unlock(
			&data->philos[i].meal_mutex);
		print_state(&data->philos[i], "died");
		return ;
	}
	pthread_mutex_unlock(
		&data->philos[i].meal_mutex);
}
