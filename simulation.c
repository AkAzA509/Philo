/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:45:07 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/18 12:01:17 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_threads(t_philo **philo, char *av[])
{
	int	i;

	i = 0;
	(*philo)->threads = malloc(sizeof(pthread_t) * (ft_atoi(av[1])));
	if (!(*philo)->threads)
	{
		ft_free(philo);
		return (0);
	}
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&(*philo)->threads[i], NULL, , NULL);
		i++;
	}
	return (1);
}

static void	init_stack(t_philo **philo, char *av[], int ac)
{
	(*philo) = malloc(sizeof(t_philo));
	if (!(*philo))
		return ;
	if (init_threads(philo, av) != 0)
	{
		ft_free(philo);
		return ;
	}
	(*philo)->time_to_eat = ft_atoi(av[4]);
	(*philo)->time_to_sleep = ft_atoi(av[5]);
	(*philo)->time_to_die = ft_atoi(av[3]);
	if (ac == 6)
		(*philo)->nb_of_meal = 0;
	else
		(*philo)->nb_of_meal = ft_atoi(av[6]);
}

void	simulation(char *av[], int ac)
{
	t_philo	*philo;

	philo = NULL;
	init_stack(&philo, av, ac);
}