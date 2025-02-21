/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:45:07 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/21 15:10:56 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	infinit_sim(t_philo *philo, int id)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		if (id == 0)
		{
			if (take_fork_first(philo, id))
				go_sleep(philo);
			else
				think(philo);
		}
		else
		{
			if (take_fork_other(philo, id))
				go_sleep(philo);
			else
				think(philo);
		}
	}
}

static void	definit_sim(t_philo *philo, int id)
{
	while (philo->meal_take <= philo->data->nb_of_meal)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		if (id == 0)
		{
			if (take_fork_first(philo, id))
				go_sleep(philo);
			else
				think(philo);
		}
		else
		{
			if (take_fork_other(philo, id))
				go_sleep(philo);
			else
				think(philo);
		}
	}
}

void	*simulation(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->data->nb_of_meal == 0)
	{
		while (1)
			infinit_sim(philo, philo->id);
	}
	else
	{
		while (philo->meal_take <= philo->data->nb_of_meal)
			definit_sim(philo, philo->id);
	}
	return (NULL);
}

void	*monitoring_thread(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		while (i < data->nb_of_philo)
		{
			if (is_dead(&data->philo[i]) == false)
				return (NULL);
			i++;
		}
		i = 0;
		usleep(2000);
	}
	return (NULL);
}

static int	launch_simulation(t_philo *philo, t_data *data, int i)
{
	pthread_t	monitoring;

	while (i < data->nb_of_philo)
	{
		philo[i].id = i;
		philo[i].last_eat = 0;
		philo[i].data = data;
		philo[i].meal_take = 0;
		if (pthread_create(&philo[i].threads, NULL, simulation, &philo[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	pthread_create(&monitoring, NULL, monitoring_thread, data);
	pthread_join(monitoring, NULL);
	while (i < data->nb_of_philo)
	{
		pthread_join(philo[i].threads, NULL);
		pthread_mutex_destroy(data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	ft_free(&philo, &data);
	return (1);
}

void	init_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->fork[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->fork[i] || pthread_mutex_init(data->fork[i], NULL) != 0)
		{
			ft_free(&philo, &data);
			return ;
		}
		data->fork_state[i] = 0;
		i++;
	}
	i = 0;
	if (launch_simulation(philo, data, i) != 1)
	{
		ft_free(&philo, &data);
		return ;
	}
}

void	init_stack(char *av[], int ac)
{
	t_philo	*philo;
	t_data	*data;

	philo = malloc(sizeof(t_philo) * ((ft_atoi(av[1]))));
	data = malloc(sizeof(t_data));
	data->fork_state = malloc(sizeof(int) * (ft_atoi(av[1])));
	data->fork = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1])));
	if (!philo || !data || !data->fork || !data->fork_state)
	{
		ft_free(&philo, &data);
		return ;
	}
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_dead = 0;
	data->philo = philo;
	data->start_time = get_time();
	pthread_mutex_init(&data->dead_lock, NULL);
	if (ac == 5)
		data->nb_of_meal = 0;
	else
		data->nb_of_meal = ft_atoi(av[5]);
	init_thread(philo, data);
}
