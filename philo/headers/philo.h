/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:09 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 17:42:01 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include "./error_codes.h"
# define INT_MAX "2147483647"

//==================== STUCTURES =====================//
typedef struct s_philo
{
	size_t			philo_id;
	size_t			time_eat;
	size_t			time_last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	glob_lock;
	pthread_mutex_t	*forks_mutex;
	size_t			phil_nb;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			eat_limit;
	size_t			t_0;
	size_t			*forks;
	t_philo			*philosophers;
	int				should_stop;
}	t_data;

//====================== UTILS =======================//
int				ft_atoi(const char *str);
void			ft_usleep(size_t time);
int				is_zero(char *nb);
int				ft_isdigit(int i);
int				print_message(t_data *data, t_philo *philo, char *msg);
size_t			get_time(void);

//===================== THREADS ======================//
int				wait_for_threads(t_data *data);
int				create_thread(pthread_t *thread, t_philo *philo,
					t_data *data, size_t i);

//====================== FORKS =======================//
int				are_forks_free(t_data *data, size_t philo_id);
void			drop_forks(t_data *data, size_t philo_id);
void			take_forks(t_data *data, size_t philo_id);
void			fill_forks(size_t *forks, size_t phil_nb);

//====================== UTILS =======================//
int				think(t_data *data, t_philo *philo);
int				eat(t_data *data, t_philo *philo);
int				p_sleep(t_philo *philo, t_data *data);

//===================== MUTEXES ======================//
pthread_mutex_t	*init_forks_mutex(size_t phil_nb);
void			destroy_forks_mutex(pthread_mutex_t *forks_mutex, size_t n);

//====================== OTHERS ======================//
int				parsing(int argc, char **argv);
void			monitoring(t_data *data);
void			*philosopher(t_philo *philo);

#endif
