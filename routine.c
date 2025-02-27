/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:08:17 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/27 16:20:32 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_data("is thinking", philo);
	usleep(5000);
}

static void	go_eat(t_philo *philo)
{
	print_data("has taken a fork", philo);
	print_data("has taken a fork", philo);
	print_data("is eating", philo);
	pthread_mutex_lock(&philo->last_eat_m);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_m);
	usleep(philo->data->eat_t * 1000);
}

void	eat(t_philo *philo, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		pthread_mutex_lock(philo->left_f);
	}
	if (someone_dead(philo) == false)
		go_eat(philo);
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
	else
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	philo->meal_take += 1;
}

void	sleeping(t_philo *philo)
{
	print_data("is sleeping", philo);
	usleep(philo->data->sleep_t * 1000);
}
