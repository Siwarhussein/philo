/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:56:05 by siwhusse          #+#    #+#             */
/*   Updated: 2026/02/15 22:30:51 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_done(t_data *data)
{
	int	idx;

	if (data->must_eat <= 0)
		return (0);
	idx = 0;
	while (idx < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[idx].meal_mutex);
		if (data->philos[idx].meals_eaten
			< data->must_eat)
		{
			pthread_mutex_unlock(
				&data->philos[idx].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(
			&data->philos[idx].meal_mutex);
		idx++;
	}
	return (1);
}

static int	scan_for_death(t_data *data, long timestamp)
{
	int	idx;

	idx = 0;
	while (idx < data->num_philos)
	{
		check_philo_death(data, idx, timestamp);
		if (check_stop(data))
			return (1);
		idx++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	long	timestamp;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		timestamp = get_time();
		if (all_philos_done(data))
		{
			set_stop(data);
			return (NULL);
		}
		if (scan_for_death(data, timestamp))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
