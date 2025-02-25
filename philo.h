/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:58:30 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:48 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_data	*data;
	pthread_t		thread;
	long			last_eat;
	int				meal_take;

	int				id;

}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	is_dead_m;
	int				is_dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	start_t_m;
	long			start_t;
	pthread_mutex_t	meal_max_m;
	int				meal_max;
	struct s_philo	*philo;
	int				nb_philo;
	int				eat_t;
	int				sleep_t;
	int				die_t;
}					t_data;

long	get_time();
int		ft_atoi(char *str);
void	print_data(char *str, t_philo *philo);
void	init_stack(char *av[], int ac);
void	eat(t_philo *philo, int i);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);
void	*monitoring(void *arg);
void	*start_sim(void *arg);
bool	check_thread(t_philo *philo);
void	ft_free(t_philo *philo, t_data *data);

#endif