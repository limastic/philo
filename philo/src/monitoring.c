/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:04:38 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/17 19:13:21 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	someone_died(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->phil_nb)
	{
		pthread_mutex_lock(&(data->glob_lock));
		if (get_time() - data->philosophers[i].time_last_meal >= data->time_die)
		{
			data->should_stop = data->philosophers[i].philo_id;
			pthread_mutex_unlock(&(data->glob_lock));
			return (1);
		}
		pthread_mutex_unlock(&(data->glob_lock));
		i++;
	}
	return (0);
}

static int	not_finished(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->phil_nb)
	{
		pthread_mutex_lock(&(data->glob_lock));
		if (data->philosophers[i].time_eat != data->eat_limit)
			return (pthread_mutex_unlock(&(data->glob_lock)), 1);
		pthread_mutex_unlock(&(data->glob_lock));
		i++;
	}
	return (0);
}

void	monitoring(t_data *data)
{
	while (not_finished(data))
	{
		if (someone_died(data))
		{
			printf("%li\t%i\tdied\n", get_time() - data->t_0, data->should_stop);
			break ;
		}
		usleep(10);
	}
}
