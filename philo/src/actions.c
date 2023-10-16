#include "../headers/philo.h"

void	take_forks(t_data *data, size_t philo_id)
{
	if (philo_id == 1)
	{
		data->forks[data->phil_nb - 1] = philo_id;
		pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
		data->forks[philo_id - 1] = philo_id;
		pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
		return ;
	}
	data->forks[philo_id - 2] = philo_id;
	pthread_mutex_unlock(&(data->forks_mutex[philo_id - 2]));
	data->forks[philo_id - 1] = philo_id;
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
		pthread_mutex_lock(&(data->forks_mutex[philo_id - 1]));
		pthread_mutex_lock(&(data->forks_mutex[data->phil_nb - 1]));
		if (data->forks[philo_id - 1] || data->forks[data->phil_nb - 1])
		{
			pthread_mutex_unlock(&(data->forks_mutex[data->phil_nb - 1]));
			pthread_mutex_unlock(&(data->forks_mutex[philo_id - 1]));
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

int	think(t_data *data, t_philo *philo)
{
//	pthread_mutex_lock(&(data->glob_lock));
//	if (data->should_stop)
//		return (pthread_mutex_unlock(&(data->glob_lock)), 1);
//	pthread_mutex_unlock(&(data->glob_lock));
	if (philo->time_eat)
		printf("%li %li is thinking\n", get_time() - data->t_0, philo->philo_id);
	while (!are_forks_free(data, philo->philo_id))
	{
		usleep(100);
	}
	return (0);
}

int p_sleep(t_philo *philo, t_data *data)
{
//	pthread_mutex_lock(&(data->glob_lock));
//	if (data->should_stop)
//		return (pthread_mutex_unlock(&(data->glob_lock)), 1);
//	pthread_mutex_unlock(&(data->glob_lock));
	(void) data;
	printf("%li %li is sleeping\n", get_time()
		- philo->data->t_0, philo->philo_id);
	ft_usleep(philo->data->time_sleep);
	return (0);
}

int	eat(t_data *data, t_philo *philo)
{
//	pthread_mutex_lock(&(data->glob_lock));
//	if (data->should_stop)
//		return (pthread_mutex_unlock(&(data->glob_lock)), 1);
//	pthread_mutex_unlock(&(data->glob_lock));
	printf("%li %li is eating\n", get_time() - data->t_0, philo->philo_id);
	pthread_mutex_lock(&(data->glob_lock));
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(data->glob_lock));
	ft_usleep(data->time_eat);
	drop_forks(data, philo->philo_id);
	philo->time_eat++;
	return (0);
}
