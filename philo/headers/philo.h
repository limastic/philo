/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:09 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/11 15:56:04 by nfaust           ###   ########.fr       */
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

typedef struct s_philo
{
	size_t			philo_id;
	size_t			time_eat;
	pthread_mutex_t	*glob_lock;
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

int			ft_atoi(const char *str);
int			is_zero(char *nb);
int			ft_isdigit(int i);
int			parsing(int argc, char **argv);
size_t		get_time(void);
void		think(t_data *data, t_philo *philo);
void		eat(t_data *data, t_philo *philo);
void		p_sleep(t_philo *philo);
void		fill_forks(size_t *forks, size_t phil_nb);


#endif
