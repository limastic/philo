/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:31:00 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/23 16:49:24 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philosopher(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->glob_lock));
	if (philo->data->should_stop)
		return (NULL);
	philo->time_last_meal = philo->data->t_0;
	pthread_mutex_unlock(&(philo->data->glob_lock));
	if (print_message(philo->data, philo->philo_id, "is thinking"))
		return (NULL);
	if (philo->time_eat == 0)
		if (philo->philo_id % 2 == 0)
			usleep(philo->data->time_eat * 500);
	while (42)
	{
		if (think(philo->data, philo) || philo->data->phil_nb == 1)
			break ;
		if (eat(philo->data, philo))
			break ;
		if (p_sleep(philo, philo->data))
			break ;
	}
	return (NULL);
}

int	init_philosophers(t_philo *philosophers, t_data *data)
{
	size_t	i;

	philosophers = malloc(sizeof(t_philo) * data->phil_nb);
	if (!philosophers)
		return (1);
	data->philosophers = philosophers;
	i = 0;
	pthread_mutex_lock(&data->glob_lock);
	while (i < data->phil_nb)
	{
		philosophers[i].data = data;
		philosophers[i].time_eat = 0;
		philosophers[i].philo_id = i + 1;
		philosophers[i].time_last_meal = get_time();
		if (create_thread(&(philosophers[i].thread),
				&(philosophers[i]), data, i))
			return (pthread_mutex_unlock(&data->glob_lock), 1);
		i++;
	}
	data->t_0 = get_time();
	pthread_mutex_unlock(&data->glob_lock);
	return (0);
}

int	get_params(int argc, char **argv, t_data *data)
{
	data->should_stop = 0;
	data->phil_nb = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc <= 5)
		data->eat_limit = -1;
	else
		data->eat_limit = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data->glob_lock, NULL))
		return (printf(E_C_GMT), 1);
	data->forks = malloc(sizeof(size_t) * data->phil_nb);
	if (!data->forks)
		return (1);
	fill_forks(data->forks, data->phil_nb);
	data->forks_mutex = init_forks_mutex(data->phil_nb);
	if (!data->forks_mutex)
		return (free(data->forks), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv))
		return (1);
	if (get_params(argc, argv, &data))
		return (1);
	if (init_philosophers(data.philosophers, &data))
		return (1);
	monitoring(&data);
	if (wait_for_threads(&data))
		return (1);
	pthread_mutex_destroy(&data.glob_lock);
	destroy_forks_mutex(data.forks_mutex, data.phil_nb);
	free(data.forks);
	free(data.philosophers);
	return (0);
}
