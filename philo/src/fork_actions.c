/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:59:19 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/17 19:46:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	take_forks_end_tab(t_data *data, size_t philo_id)
{
	data->forks[philo_id - 1] = philo_id;
	if (print_message(data, data->philosophers + philo_id - 1,
			"has taken a fork"))
	{
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
		return ;
	}
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
	while (philo_id == data->phil_nb)
	{
		usleep(500);
		if (print_message(data, data->philosophers, NULL))
			return ;
	}
	data->forks[data->phil_nb - 1] = philo_id;
	if (print_message(data, data->philosophers + philo_id - 1,
			"has taken a fork"))
	{
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
		return ;
	}
	pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
	return ;
}

void	take_forks(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
		return (take_forks_end_tab(data, philo_id), (void)0);
	data->forks[philo_id - 2] = philo_id;
	if (print_message(data, data->philosophers + philo_id - 1,
			"has taken a fork"))
	{
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		return ;
	}
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
	data->forks[philo_id - 1] = philo_id;
	if (print_message(data, data->philosophers + philo_id - 1,
			"has taken a fork"))
	{
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		return ;
	}
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
}

void	drop_forks(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
		pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		data->forks[philo_id - 1] = 0;
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		data->forks[data->phil_nb - 1] = 0;
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
		return ;
	}
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
	data->forks[philo_id - 1] = 0;
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 2]));
	data->forks[philo_id - 2] = 0;
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
}

int	are_forks_free(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		if (data->phil_nb != philo_id)
			pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		if (data->forks[philo_id - 1] || data->forks[data->phil_nb - 1])
		{
			pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
			pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
			return (0);
		}
		return (take_forks(data, philo_id), 1);
	}
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 2]));
	if (data->forks[philo_id - 1] || data->forks[philo_id - 2])
		return (pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2])),
			pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1])), 0);
	return (take_forks(data, philo_id), 1);
}
