/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:30:48 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/19 16:14:48 by ggirault         ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		threads;
	int				id;
	long			last_eat;
}					t_philo;

typedef struct s_time
{
	long			sec;
	long			usec;
}					t_time;

typedef struct s_data
{
	pthread_mutex_t	**fork;
	int				*fork_state;
	int				nb_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_of_meal;
	struct s_time	*time;
	long			start_time;
	int			current_time;
 }					t_data;

//---------------[ Util$]-----------------//

int					ft_atoi(char *str);
void				ft_free(t_philo **philo, t_data **data);
long				get_time();

//---------------[ $imulation ]-----------//

void				init_stack(char *av[], int ac);
bool				take_fork(t_philo *philo, int first, int i);
void				go_sleep(t_philo *philo);
void				think(t_philo *philo);

#endif