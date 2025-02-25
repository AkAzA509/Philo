/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:39:49 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/25 16:14:55 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool someone_dead(t_philo *philo)
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

static void limited_sim(t_philo *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&philo->data->meal_max_m);
	while (i <= philo->data->meal_max)
	{
		pthread_mutex_unlock(&philo->data->meal_max_m);
		if (someone_dead(philo))
			return;
		think(philo);
		if (someone_dead(philo))
			return;
		eat(philo, philo->id);
		if (someone_dead(philo))
			return;
		sleeping(philo);
		if (someone_dead(philo))
			return;
		i++;
	}
}

static void unlimited_sim(t_philo *philo)
{
	while (1)
	{
		//printf("Philo %d: début de cycle\n", philo->id);

		if (someone_dead(philo))
		{
			//printf("Philo %d: quelqu'un est mort au début\n", philo->id);
			return ;
		}
		//printf("Philo %d: commence à penser\n", philo->id);
		think(philo);
		//print_data(": a fini de penser", philo);
		if (someone_dead(philo))
		{
		//	printf("Philo %d: quelqu'un est mort après penser\n", philo->id);
			return ;
		}
		//printf("Philo %d: commence à manger\n", philo->id);
		eat(philo, philo->id);
		//print_data(": a fini de manger\n", philo);
		if (someone_dead(philo))
		{
		//	printf("Philo %d: quelqu'un est mort après manger\n", philo->id);
			return ;
		}
		//printf("Philo %d: commence à dormir\n", philo->id);
		sleeping(philo);
		//printf("Philo %d: a fini de dormir\n", philo->id);
		//printf("Philo %d: fin de cycle\n", philo->id);
	}
}

void *start_sim(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_max_m);
	if (philo->data->meal_max == 0)
	{
		pthread_mutex_unlock(&philo->data->meal_max_m);
		unlimited_sim(philo);
	}
	else
		limited_sim(philo);
	return (NULL);
}

void *monitoring(void *arg)
{
	t_data *data;
	int i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		while (i < data->nb_philo)
		{
			if (check_thread(&data->philo[i]) == false)
				return (NULL);
			i++;
		}
		i = 0;
		usleep(2000);
	}
	return (NULL);
}