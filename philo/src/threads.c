/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:30:57 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 17:41:52 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	wait_for_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->phil_nb)
	{
		printf("je suis passe la \n");
		if (pthread_join(data->philosophers[i].thread, NULL))
		{
			printf(E_W_TH, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_thread(pthread_t *thread, t_philo *philo, t_data *data, size_t i)
{
	if (pthread_create(thread, NULL, (void *)philosopher, philo))
	{
		printf(E_C_TH, i + 1);
		destroy_forks_mutex(data->forks_mutex, data->phil_nb);
		data->should_stop = 1;
		data->phil_nb = i;
		pthread_mutex_unlock(&(data->glob_lock));
		wait_for_threads(data);
		free(data->forks);
		free(data->philosophers);
		return (1);
	}
	return (0);
}
