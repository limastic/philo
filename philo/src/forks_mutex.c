/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:07:00 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/17 16:07:56 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	destroy_forks_mutex(pthread_mutex_t *forks_mutex, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&(forks_mutex[i++]));
	free(forks_mutex);
}

pthread_mutex_t	*init_forks_mutex(size_t phil_nb)
{
	pthread_mutex_t	*forks_mutex;
	size_t			i;

	forks_mutex = malloc(sizeof(pthread_mutex_t) * phil_nb);
	if (!forks_mutex)
		return (NULL);
	i = 0;
	while (i < phil_nb)
	{
		if (pthread_mutex_init(&(forks_mutex[i++]), NULL))
			return (destroy_forks_mutex(forks_mutex, i), NULL);
	}
	return (forks_mutex);
}
