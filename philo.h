/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:30:48 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/18 11:59:08 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	**threads;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			nb_of_meal;
}			t_philo;

//---------------[ Util$]-----------------0//

int		ft_atoi(char *str);
void	ft_free(t_philo **philo);

//---------------[ Simulation ]-----------//

void	simulation(char *av[], int ac);
#endif