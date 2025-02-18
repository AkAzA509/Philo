/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:45:07 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/18 16:55:29 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *thread)
{
	t_philo *philo = (t_philo *)thread;
	int i = 0;
	if (philo->data->nb_of_meal != 0)
	{
		while(i < philo->data->nb_of_meal)
		{
			printf("Philosophe %d a commencé !\n", philo->id);
			i++;
		}
	}
	return (NULL);
}

static int	init_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		philo[i].id = i;
		philo[i].data = data;
		if (pthread_create(&philo[i].threads, NULL, test, &philo[i]) != 0)
			return (0);
		philo[i].last_eat = 0;
		i++;
	}

	for (int i = 0; i < philo->data->nb_of_philo; i++)
		pthread_join(philo[i].threads, NULL);
	ft_free(&philo, &data);
	return (1);
}

void	init_stack(char *av[], int ac)
{	
	t_philo	*philo;
	t_data	*data;

	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	data = malloc(sizeof(t_data));
	if (!philo || !data)
	{
		ft_free(&philo, &data);
		return ;
	}
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_die = ft_atoi(av[2]);
	if (ac == 5)
		data->nb_of_meal = 0;
	else
		data->nb_of_meal = ft_atoi(av[5]);
	if (init_threads(philo, data) != 0)
	{
		ft_free(&philo, &data);
		return ;
	}
}
