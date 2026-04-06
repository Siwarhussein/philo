/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:38:29 by siwhusse          #+#    #+#             */
/*   Updated: 2026/04/05 18:29:19 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		return (1);
	}
	data->stop = 0;
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			pthread_mutex_destroy(&data->stop_mutex);
			pthread_mutex_destroy(&data->print_mutex);
			return (1);
		}
	}
	return (0);
}

static int	init_single_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].left_fork = &data->forks[i]; 
	data->philos[i].right_fork = &data->forks[(i + 1)
		% data->num_philos];
	data->philos[i].last_meal_time = get_time();
	data->philos[i].meals_eaten = 0;
	data->philos[i].data = data;
	if (pthread_mutex_init(&data->philos[i].meal_mutex,
			NULL) != 0)
		return (1);
	return (0);
}

static void	cleanup_init_error(t_data *data, int failed_index)
{
	int	j;

	j = 0;
	while (j < failed_index)
	{
		pthread_mutex_destroy(&data->philos[j].meal_mutex);
		j++;
	}
	j = 0;
	while (j < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		cleanup(data);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (init_single_philo(data, i))
		{
			cleanup_init_error(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}
