/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:59:19 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/24 20:23:53 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	invert_forks(size_t *left_fork, size_t *right_fork)
{
	size_t	temp;

	temp = *right_fork;
	*right_fork = *left_fork;
	*left_fork = temp;
}

static void	wait_for_death(t_data *data)
{
	while (!print_message(data, 0, NULL))
		usleep(500);
}

static void	take_forks(t_data *data, size_t philo_id)
{
	size_t	left_fork;
	size_t	right_fork;

	left_fork = (philo_id - 1) % data->phil_nb;
	right_fork = (philo_id) % data->phil_nb;
	if (philo_id == data->phil_nb)
		invert_forks(&left_fork, &right_fork);
	pthread_mutex_lock(&(data->forks_mutex[left_fork]));
	data->forks[left_fork] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[left_fork]));
	if (print_message(data, philo_id, "has taken a fork"))
		return ;
	if (1 == data->phil_nb)
		return (wait_for_death(data), (void)0);
	pthread_mutex_lock(&(data->forks_mutex[right_fork]));
	data->forks[right_fork] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[right_fork]));
	print_message(data, philo_id, "has taken a fork");
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
	if (philo_id == data->phil_nb)
		invert_forks(&left_fork, &right_fork);
	pthread_mutex_lock(&(data->forks_mutex[right_fork]));
	if (left_fork != right_fork)
		pthread_mutex_lock(&(data->forks_mutex[left_fork]));
	if (data->forks[right_fork] || data->forks[left_fork])
		return (pthread_mutex_unlock(&(data->forks_mutex[left_fork])),
			pthread_mutex_unlock(&(data->forks_mutex[right_fork])), 0);
	if (left_fork != right_fork)
		pthread_mutex_unlock(&(data->forks_mutex[left_fork]));
	pthread_mutex_unlock(&(data->forks_mutex[right_fork]));
	return (take_forks(data, philo_id), 1);
}
