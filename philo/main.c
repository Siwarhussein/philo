/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:26:24 by siwhusse          #+#    #+#             */
/*   Updated: 2026/02/15 22:22:17 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			routine, &data->philos[i]);
		i++;
	}
	usleep(2000);
	pthread_create(monitor, NULL, monitor_routine, data);
	return (0);
}

static void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (argc != 5 && argc != 6)
		return (write(2, "Error: Invalid arguments.\n", 26), 1);
	if (!pars_args(&data, argc, argv))
		return (write(2, "Error: Invalid arguments.\n", 26), 1);
	if (init_data(&data) || init_forks(&data)
		|| init_philos(&data))
		return (1);
	data.start_time = get_time();
	start_threads(&data, &monitor);
	join_threads(&data, monitor);
	cleanup(&data);
	return (0);
}
