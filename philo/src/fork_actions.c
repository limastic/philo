/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:59:19 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/23 19:03:41 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	take_forks(t_data *data, size_t philo_id)
{
	size_t	left_fork;
	size_t	right_fork;

	left_fork = (philo_id - 1) % data->phil_nb;
	right_fork = (philo_id) % data->phil_nb;
	data->forks[left_fork] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[left_fork]));
	if (print_message(data, data->philosophers + philo_id - 1,
			"has taken a fork"))
	{
		if (right_fork != left_fork)
			pthread_mutex_unlock(&(data->forks_mutex[right_fork]));
		return ;
	}
	while (1 == data->phil_nb)
	{
		usleep(500);
		if (print_message(data, data->philosophers, NULL))
			return ;
	}
	data->forks[right_fork] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[right_fork]));
	print_message(data, data->philosophers + philo_id - 1,
		"has taken a fork");
}

void	drop_forks(t_data *data, size_t philo_id)
{
	size_t	left_fork;
	size_t	right_fork;

	left_fork = (philo_id - 1) % data->phil_nb;
	right_fork = (philo_id) % data->phil_nb;
	pthread_mutex_lock(&(data->forks_mutex[left_fork]));
	data->forks[left_fork] = 0;
	pthread_mutex_unlock(&(data->forks_mutex[left_fork]));
	pthread_mutex_lock(&(data->forks_mutex[right_fork]));
	data->forks[right_fork] = 0;
	pthread_mutex_unlock(&(data->forks_mutex[right_fork]));
}

int	are_forks_free(t_data *data, size_t philo_id)
{
	size_t	left_fork;
	size_t	right_fork;

	left_fork = (philo_id - 1) % data->phil_nb;
	right_fork = (philo_id) % data->phil_nb;
	pthread_mutex_lock(&(data->forks_mutex[right_fork]));
	if (left_fork != right_fork)
		pthread_mutex_lock(&(data->forks_mutex[left_fork]));
	if (data->forks[right_fork] || data->forks[left_fork])
		return (pthread_mutex_unlock(&(data->forks_mutex[left_fork])),
			pthread_mutex_unlock(&(data->forks_mutex[right_fork])), 0);
	return (take_forks(data, philo_id), 1);
}
