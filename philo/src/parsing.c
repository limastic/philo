/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:36:27 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/07 16:20:10 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	check_format(char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (is_zero(argv[i]))
			return (1);
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]))
				return (1);
		i++;
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf(WRONG_ARG), 1);
	if (check_format(argv))
		return (printf(WRONG_F), 1);
	return (0);
}
