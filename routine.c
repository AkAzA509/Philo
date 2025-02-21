/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:10:28 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/21 11:17:47 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(), philo->id);
	usleep(50000);
}

bool	take_fork_first(t_philo *philo, int i)
{
	if (philo->data->fork_state[i] == 0 && philo->data->fork_state[i
		+ philo->data->nb_of_philo - 1] == 0)
	{
		pthread_mutex_lock(philo->data->fork[i + philo->data->nb_of_philo - 1]);
		pthread_mutex_lock(philo->data->fork[i]);
		philo->data->fork_state[i + philo->data->nb_of_philo - 1] = 1;
		philo->data->fork_state[i] = 1;
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		philo->last_eat = get_time();
		philo->data->fork_state[i + philo->data->nb_of_philo - 1] = 0;
		philo->data->fork_state[i] = 0;
		pthread_mutex_unlock(philo->data->fork[i + philo->data->nb_of_philo
			- 1]);
		pthread_mutex_unlock(philo->data->fork[i]);
		philo->meal_take += 1;
		return (true);
	}
	return (false);
}

bool	take_fork_other(t_philo *philo, int i)
{
	if (philo->data->fork_state[i] == 0 && philo->data->fork_state[i - 1] == 0)
	{
		pthread_mutex_lock(philo->data->fork[i - 1]);
		pthread_mutex_lock(philo->data->fork[i]);
		philo->data->fork_state[i - 1] = 1;
		philo->data->fork_state[i] = 1;
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		philo->last_eat = get_time();
		philo->data->fork_state[i - 1] = 0;
		philo->data->fork_state[i] = 0;
		pthread_mutex_unlock(philo->data->fork[i - 1]);
		pthread_mutex_unlock(philo->data->fork[i]);
		philo->meal_take += 1;
		return (true);
	}
	return (false);
}

bool	is_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_time();
	if ((current_time - philo->last_eat) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->is_dead == 0)
		{
			philo->data->is_dead = 1;
			printf("%ld %d died\n", current_time, philo->id);
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (false);
	}
	return (true);
}
