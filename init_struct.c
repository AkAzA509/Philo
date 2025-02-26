/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:09:02 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/26 15:12:29 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_data *data, pthread_t monitoring_t,
		int i)
{
	data->start_t = get_time();
	data->philo = philo;
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i;
		philo[i].last_eat = data->start_t;
		philo[i].left_f = &data->fork[i];
		philo[i].right_f = &data->fork[(i + 1) % data->nb_philo];
		philo[i].meal_take = 0;
		pthread_mutex_init(&philo[i].last_eat_m, NULL);
		if (pthread_create(&philo[i].thread, NULL, start_sim, &philo[i]) != 0)
			return ;
		i++;
	}
	pthread_create(&monitoring_t, NULL, monitoring, data);
	pthread_join(monitoring_t, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	ft_free(philo, data);
}

void	init_fork(t_data **data, t_philo *philo, int i)
{
	while (i < (*data)->nb_philo)
	{
		if (pthread_mutex_init(&(*data)->fork[i], NULL) != 0)
		{
			ft_free(philo, *data);
			return ;
		}
		i++;
	}
}

static t_data	*init_data(t_data *data, char *av[], int ac, t_philo *philo)
{
	int	i;

	data = malloc(sizeof(t_data));
	data->nb_philo = ft_atoi(av[1]);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data || !data->fork)
	{
		ft_free(philo, data);
		return (NULL);
	}
	data->die_t = ft_atoi(av[2]);
	data->eat_t = ft_atoi(av[3]);
	data->sleep_t = ft_atoi(av[4]);
	data->is_dead = 0;
	pthread_mutex_init(&data->is_dead_m, NULL);
	pthread_mutex_init(&data->start_t_m, NULL);
	pthread_mutex_init(&data->meal_max_m, NULL);
	if (ac == 6)
		data->meal_max = ft_atoi(av[5]);
	else
		data->meal_max = 0;
	i = 0;
	init_fork(&data, philo, i);
	return (data);
}

void	init_stack(char *av[], int ac)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	monitoring;
	int			i;

	i = 0;
	data = NULL;
	philo = NULL;
	monitoring = 0;
	data = init_data(data, av, ac, philo);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
	{
		ft_free(philo, data);
		return ;
	}
	init_philo(philo, data, monitoring, i);
}
