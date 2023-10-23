/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:03:00 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 18:56:42 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	think(t_data *data, t_philo *philo)
{
	if (philo->time_eat)
	{
		if (print_message(data, philo, "is thinking"))
			return (1);
		if (data->phil_nb % 2 != 0 && data->time_eat >= data->time_sleep)
			ft_usleep(data->time_eat - data->time_sleep + 1);
	}
	while (!are_forks_free(data, philo->philo_id))
	{
		usleep(10);
		if (print_message(data, philo, NULL))
			return (1);
	}
	return (0);
}

int	p_sleep(t_philo *philo, t_data *data)
{
	if (print_message(data, philo, "is sleeping"))
		return (1);
	ft_usleep(philo->data->time_sleep);
	return (0);
}

int	eat(t_data *data, t_philo *philo)
{
	if (print_message(data, philo, "is eating"))
		return (1);
	pthread_mutex_lock(&(data->glob_lock));
	philo->time_last_meal = get_time();
	philo->time_eat++;
	pthread_mutex_unlock(&(data->glob_lock));
	ft_usleep(data->time_eat);
	drop_forks(data, philo->philo_id);
	return (0);
}
