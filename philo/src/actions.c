#include "../headers/philo.h"

void	take_forks(t_data *data, size_t philo_id)
{
	if (philo_id - 2 < 0)
	{
		data->forks[philo_id - 1] = philo_id;
		data->forks[data->phil_nb - 1] = philo_id;
		return ;
	}
	data->forks[philo_id - 1] = philo_id;
	data->forks[philo_id - 2] = philo_id;
}

void	drop_forks(t_data *data, size_t philo_id)
{
	if (philo_id - 2 < 0)
	{
		data->forks[philo_id - 1] = 0;
		data->forks[data->phil_nb - 1] = 0;
		return ;
	}
	data->forks[philo_id - 1] = 0;
	data->forks[philo_id - 2] = 0;
}

int are_forks_free(t_data *data, size_t philo_id)
{
	if (philo_id - 2 < 0)
	{
		if (data->forks[philo_id - 1] || data->forks[data->phil_nb - 1])
			return (0);
		return (take_forks(data, philo_id), 1);
	}
	if (data->forks[philo_id - 1] || data->forks[philo_id - 2])
		return (0);
	return (take_forks(data, philo_id), 1);
}

void	think(t_data *data, t_philo *philo)
{
	printf("%li %li is thinking\n", get_time() - data->t_0, philo->philo_id);
	if (philo->time_eat == 0)
		if (philo->philo_id % 2 == 0)
			usleep(10);
	pthread_mutex_lock(&(data->fork_lock));
	while (!are_forks_free(data, philo->philo_id))
	{
		pthread_mutex_unlock(&(data->fork_lock));
		usleep(10);
		pthread_mutex_lock(&(data->fork_lock));
	}
	pthread_mutex_unlock(&(data->fork_lock));
}

void	eat(t_data *data, t_philo *philo)
{
	printf("%li %li is eating\n", get_time() - data->t_0, philo->philo_id);
	usleep(data->time_eat * 1000);
	pthread_mutex_lock(&(data->fork_lock));
	drop_forks(data, philo->philo_id);
	pthread_mutex_unlock(&(data->fork_lock));
	philo->time_eat++;
}