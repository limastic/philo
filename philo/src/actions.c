#include "../headers/philo.h"

void	take_forks(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
//		pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		data->forks[philo_id - 1] = philo_id;
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
//		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		data->forks[data->phil_nb - 1] = philo_id;
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		return ;
	}
//	pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
//	pthread_mutex_lock(&(data->forks_mutex[philo_id - 2]));
	data->forks[philo_id - 1] = philo_id;
	data->forks[philo_id - 2] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
}

void	drop_forks(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
		pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		data->forks[philo_id - 1] = 0;
		data->forks[data->phil_nb - 1] = 0;
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		return ;
	}
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 2]));
	data->forks[philo_id - 1] = 0;
	data->forks[philo_id - 2] = 0;
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
}

int	are_forks_free(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
		pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		if (data->forks[philo_id - 1] || data->forks[data->phil_nb - 1])
			return (
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1])),
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1])), 0);
		return (take_forks(data, philo_id), 1);
	}
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
	pthread_mutex_lock(&(data->forks_mutex[philo_id - 2]));
	if (data->forks[philo_id - 1] || data->forks[philo_id - 2])
		return (
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2])),
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1])), 0);
	return (take_forks(data, philo_id), 1);
}

void	think(t_data *data, t_philo *philo)
{
	printf("%li %li is thinking\n", get_time() - data->t_0, philo->philo_id);
	while (!are_forks_free(data, philo->philo_id))
	{
		usleep(100);
//		printf("%li\n", philo->philo_id);
	}
}

void	p_sleep(t_philo *philo)
{
	size_t	initial_time;

	printf("%li %li is sleeping\n", get_time() - philo->data->t_0, philo->philo_id);
	initial_time = get_time();
	while (get_time() - initial_time < philo->data->time_sleep)
		usleep(100);
}

void	eat(t_data *data, t_philo *philo)
{
	printf("%li %li is eating\n", get_time() - data->t_0, philo->philo_id);
	usleep(data->time_eat * 1000);
	drop_forks(data, philo->philo_id);
	philo->time_eat++;
}