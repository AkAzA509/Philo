/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:30:48 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/18 16:53:01 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		threads;
	int				id;
	long			last_eat;
}					t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_of_meal;
}					t_data;

//---------------[ Util$]-----------------//

int					ft_atoi(char *str);
void				ft_free(t_philo **philo, t_data **data);

//---------------[ $imulation ]-----------//

void				init_stack(char *av[], int ac);

#endif