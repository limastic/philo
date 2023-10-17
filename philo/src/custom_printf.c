/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:03 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/17 18:50:16 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	print_li(size_t i)
{
	char	c;

	if (i / 10 > 0)
	{
		print_li(i / 10);
		c = i % 10 + 48;
		write (1, &c, 1);
	}
	else
	{
		c = i + 48;
		write(1, &c, 1);
	}
}

void	custom_printf(size_t time, size_t philo_id, char *message)
{
	size_t	i;

	print_li(time);
	write (1, " ", 1);
	print_li(philo_id);
	write (1, " ", 1);
	i = 0;
	while (message[i])
		write(1, &(message[i++]), 1);
	write(1, "\n", 1);
}
