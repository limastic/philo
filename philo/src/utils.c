/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:52:26 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 18:44:15 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	is_zero(char *nb)
{
	size_t	i;

	i = 0;
	while (nb[i])
		if (nb[i++] != '0')
			return (0);
	return (1);
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			seconds;
	size_t			u_seconds;
	size_t			m_seconds;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	u_seconds = time.tv_usec;
	m_seconds = u_seconds / 1000;
	m_seconds += seconds * 1000;
	return (m_seconds);
}

void	ft_usleep(size_t time)
{
	size_t	initial_time;

	initial_time = get_time();
	while (get_time() - initial_time < time)
	{
		usleep(100);
	}
}

void	fill_forks(size_t *forks, size_t phil_nb)
{
	size_t	i;

	i = 0;
	while (i < phil_nb)
		forks[i++] = 0;
}

int	print_message(t_data *data, size_t philo_id, char *msg)
{
	pthread_mutex_lock(&(data->glob_lock));
	if (data->should_stop)
	{
		pthread_mutex_unlock(&(data->glob_lock));
		return (1);
	}
	if (!msg)
		return (pthread_mutex_unlock(&(data->glob_lock)), 0);
	printf("%li\t%li\t%s\n", get_time() - data->t_0, philo_id, msg);
	pthread_mutex_unlock(&(data->glob_lock));
	return (0);
}
