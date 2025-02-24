/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:14:28 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/24 15:31:31 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if ((str[i] >= 7 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || (str[i] == '+' && str[i + 1] == '+'))
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res *10 + (str[i] - 48);
		i++;
	}
	return (res);	
}

long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_data(char *str, t_philo *philo)
{
	long	current_t;

	current_t = get_time();
	pthread_mutex_lock(&philo->data->start_t_m);
	printf("%ld ms %d %s\n",current_t - philo->data->start_t, philo->id, str);
	pthread_mutex_unlock(&philo->data->start_t_m);
}

void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;

	if(data)
	{
		pthread_mutex_destroy(&data->is_dead_m);
		pthread_mutex_destroy(&data->start_t_m);
		pthread_mutex_destroy(&data->meal_max_m);
		free(data->fork);
		free(data);
		data = NULL;
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
}

bool	check_thread(t_philo *philo)
{
	long	current_time;

	current_time = get_time();
	if ((current_time - philo->last_eat) >= philo->data->die_t)
	{
		pthread_mutex_lock(&philo->data->is_dead_m);
		if (philo->data->is_dead == 0)
		{
			philo->data->is_dead = 1;
			print_data("died", philo);
		}
		pthread_mutex_unlock(&philo->data->is_dead_m);
		return (false);
	}
	return (true);
}