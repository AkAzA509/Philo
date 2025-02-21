/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:49:45 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/21 14:32:51 by ggirault         ###   ########.fr       */
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

void	ft_free(t_philo **philo, t_data **data)
{
	int	i;

	i = 0;
	if(*data)
	{
		while(i < (*data)->nb_of_philo)
		{
			free((*data)->fork[i]);
			i++;
		}
		free((*data)->fork);
		free((*data)->fork_state);
		free(*data);
		*data = NULL;
	}
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
}

long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}