/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:39:49 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/26 15:09:01 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_m);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->is_dead_m);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->is_dead_m);
	return (false);
}

static void	limited_sim(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->meal_max_m);
		if (i == philo->data->meal_max)
		{
			pthread_mutex_unlock(&philo->data->meal_max_m);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meal_max_m);
		if (someone_dead(philo))
			return ;
		think(philo);
		if (someone_dead(philo))
			return ;
		eat(philo, philo->id);
		if (someone_dead(philo))
			return ;
		sleeping(philo);
		if (someone_dead(philo))
			return ;
		i++;
	}
}

static void	unlimited_sim(t_philo *philo)
{
	while (1)
	{
		if (someone_dead(philo))
			return ;
		think(philo);
		if (someone_dead(philo))
			return ;
		eat(philo, philo->id);
		if (someone_dead(philo))
			return ;
		sleeping(philo);
		if (someone_dead(philo))
			return ;
	}
}

void	*start_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_max_m);
	if (philo->data->meal_max == 0)
	{
		pthread_mutex_unlock(&philo->data->meal_max_m);
		unlimited_sim(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->meal_max_m);
		limited_sim(philo);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		while (i < data->nb_philo)
		{
			if (check_thread(&data->philo[i]) == false)
			{
				return (NULL);
			}
			i++;
		}
		i = 0;
		usleep(2000);
	}
	return (NULL);
}
