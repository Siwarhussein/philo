/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwhusse <siwhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:56:29 by siwhusse          #+#    #+#             */
/*   Updated: 2026/04/06 18:44:29 by siwhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	precise_sleep(philo->data->time_to_eat * 1000,
		philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

static int	done_eating(t_philo *philo)
{
	int	result;

	if (philo->data->must_eat <= 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	result = philo->meals_eaten
		>= philo->data->must_eat;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}

static int	eat_cycle(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		print_state(philo, "has taken a fork");
		precise_sleep(philo->data->time_to_die * 1000,
			philo);
		return (1);
	}
	lock_forks(philo);
	if (check_stop(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	philo_eat(philo);
	if (done_eating(philo)
		|| check_stop(philo->data))
		return (1);
	print_state(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep * 1000,
		philo);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		precise_sleep(
			philo->data->time_to_die * 1000, // convert to microseconds
			philo);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		precise_sleep(500, philo); // to avoid deadlock when all philosophers pick up their left fork at the same time
	while (!check_stop(philo->data))
	{
		print_state(philo, "is thinking");
		if (eat_cycle(philo))
			break ;
	}
	return (NULL);
}
