/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:09 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/07 18:20:02 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "./error_codes.h"

typedef struct s_philo
{
    int philo_id;
}           t_philo;

typedef struct s_data
{
	size_t			phil_nb;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			eat_limit;
	pthread_t		*threads;
	pthread_mutex_t	lock;
}			t_data;

int			ft_atoi(const char *str);
int			is_zero(char *nb);
int			ft_isdigit(int i);
t_data		*parsing(int argc, char **argv);

#endif
