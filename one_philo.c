/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:31:53 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/28 12:26:54 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_sim(void *arg)
{
	t_data	*data;
	long	current_t;

	data = (t_data *)arg;
	current_t = get_time();
	pthread_mutex_lock(&data->start_t_m);
	printf("%ld %d is thinking\n", current_t - data->start_t, data->philo->id);
	pthread_mutex_unlock(&data->start_t_m);
	usleep(data->die_t * 1000);
	current_t = get_time();
	pthread_mutex_lock(&data->start_t_m);
	printf("%ld %d died\n", current_t - data->start_t, data->philo->id);
	pthread_mutex_unlock(&data->start_t_m);
	return (NULL);
}

void	launch_one_philo(t_philo *philo, t_data *data)
{
	data->start_t = get_time();
	data->philo = philo;
	philo->data = data;
	philo->id = 0;
	philo->last_eat = data->start_t;
	philo->left_f = &data->fork[0];
	philo->right_f = &data->fork[(0 + 1) % data->nb_philo];
	philo->meal_take = 0;
	pthread_mutex_init(&philo->last_eat_m, NULL);
	if (pthread_create(&philo->thread, NULL, one_sim, data) != 0)
		return ;
	pthread_join(philo->thread, NULL);
	ft_free(philo, data);
}
