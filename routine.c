/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:10:28 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/19 16:14:22 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_philo *philo, int first, int i)
{
	if (first == 1 && (philo->data->fork_state[i] == 0
			&& philo->data->fork_state[i + philo->data->nb_of_philo - 1] == 0))
	{
		pthread_mutex_lock(philo->data->fork[i]);
		pthread_mutex_lock(philo->data->fork[i + philo->data->nb_of_philo - 1]);
		philo->data->fork_state[i] = 1;
		philo->data->fork_state[i + philo->data->nb_of_philo - 1] = 1;
		printf("%ld %d has taken a fork\n", philo->data->start_time, philo->id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->data->fork[i]);
		pthread_mutex_unlock(philo->data->fork[i + philo->data->nb_of_philo
			- 1]);
		philo->data->fork_state[i] = 0;
		philo->data->fork_state[i + philo->data->nb_of_philo - 1] = 0;
		return (true);
	}
	else if (first == 0 && (philo->data->fork_state[i] == 0
			&& philo->data->fork_state[i - 1] == 0))
	{
		pthread_mutex_lock(philo->data->fork[i]);
		pthread_mutex_lock(philo->data->fork[i - 1]);
		philo->data->fork_state[i] = 1;
		philo->data->fork_state[i - 1] = 1;
		printf("%ld %d has taken a fork\n", philo->data->start_time, philo->id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->data->fork[i]);
		pthread_mutex_unlock(philo->data->fork[i - 1]);
		philo->data->fork_state[i] = 0;
		philo->data->fork_state[i - 1] = 0;
		return (true);
	}
	else
		return (false);
}

void	go_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", philo->data->start_time, philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", philo->data->start_time, philo->id);
	usleep(5000);
}
