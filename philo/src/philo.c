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

void	*philosopher(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->glob_lock));
	pthread_mutex_unlock(&(philo->data->glob_lock));
	while (philo->time_eat != philo->data->eat_limit)
	{
		printf("%li\n", philo->data->eat_limit);
		think(philo->data, philo);
		eat(philo->data, philo);
		printf("id : %li mange :%li\n", philo->philo_id, philo->time_eat);
	}
	return (NULL);
}

int	wait_for_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->phil_nb)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (printf("error while waiting for thread %li, [%li]\n", i, data->philosophers[i].thread), 1);
		i++;
	}
	return (0);
}

int init_philosophers(t_philo *philosophers, t_data *data)
{
	size_t	i;

	philosophers = malloc(sizeof(t_philo) * data->phil_nb);
	if (!philosophers)
		return (1);
	data->philosophers = philosophers;
	pthread_mutex_init(&data->glob_lock, NULL);
	i = 0;
	pthread_mutex_lock(&data->glob_lock);
	while (i < data->phil_nb)
	{
		philosophers[i].data = data;
		philosophers[i].time_eat = 0;
		philosophers[i].philo_id = i + 1;
		philosophers[i].glob_lock = &data->glob_lock;
		if (pthread_create(&(philosophers[i].thread), NULL, (void *)philosopher, &philosophers[i]))
			return (printf("E_C_TH %li.", i + 1), 1);
		i++;
	}
	data->t_0 = get_time();
	pthread_mutex_unlock(&data->glob_lock);
	return (0);
}

int	get_params(int argc, char **argv, t_data *data)
{
	pthread_mutex_init(&(data->fork_lock), NULL);
	data->phil_nb = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc < 5)
		data->eat_limit = -1;
	else
		data->eat_limit = ft_atoi(argv[5]);
	data->forks = malloc(sizeof(size_t) * data->phil_nb);
	if (!data->forks)
		return (1);
	memset(data->forks, 0, data->phil_nb);
	return (0);
}

void	monitoring(t_data *data)
{

}

int	main(int argc, char **argv)
{
	t_data	data;
	if (parsing(argc, argv))
		return (1);
	if(get_params(argc, argv, &data))
		return (1);
	if(init_philosophers(data.philosophers, &data) || wait_for_threads(&data))
		return (1);
	pthread_mutex_destroy(&data.glob_lock);
	free(data.philosophers);
	return (0);
}
