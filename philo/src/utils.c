/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:52:26 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/11 16:03:49 by nfaust           ###   ########.fr       */
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

void	fill_forks(size_t *forks, size_t phil_nb)
{
	size_t	i;

	i = 0;
	while (i < phil_nb)
		forks[i++] = 0;
}
