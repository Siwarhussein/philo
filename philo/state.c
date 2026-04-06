/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:29:02 by siwhusse          #+#    #+#             */
/*   Updated: 2026/02/15 22:34:42 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	print_state(t_philo *philo, char *state)
{
	long	timestamp;
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	if (ft_strcmp(state, "died") == 0)
	{
		if (check_stop(data))
		{
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		set_stop(data);
	}
	else if (check_stop(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	timestamp = get_time() - data->start_time;
	printf("%ld %d %s\n",
		timestamp, philo->id, state);
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}
