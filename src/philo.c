/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:31:00 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/07 18:52:35 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philosopher(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&(data->lock));
	printf("je suis le thread %d\n", 1);
	pthread_mutex_unlock(&(data->lock));
	pthread_exit(NULL);
}

int	wait_for_threads(t_data *data)
{
	size_t	i;
	int		error_code;

	i = 0;
	while (i < data->phil_nb)
	{
		error_code = pthread_join(data->threads[i], NULL);
		if (error_code)
			return (printf("error while waiting for thread %li : %d", i + 1, error_code), 1);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	size_t	i;
	int		error_code;

	i = 0;
	while (i < data->phil_nb)
	{
		error_code = pthread_create(&(data->threads[i]), NULL, philosopher, data);
		if (error_code)
			return (printf("error creating thread %li : %d", i + 1, error_code), 1);
		i++;
	}
	return (0);
}

int	philo(t_data *data)
{
	pthread_mutex_init(&(data->lock), NULL);
	data->threads = malloc(sizeof(pthread_t) * data->phil_nb);
	if (!data->threads)
		return (1);
	if (create_threads(data))
		return (1);
	if (wait_for_threads(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parsing(argc, argv);
	if (!data)
		return (1);
	philo(data);
	free(data);
	return (0);
}
