/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:36:27 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 16:46:41 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	check_overflow(char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10)
			return (1);
		else if (ft_strlen(argv[i]) < 10)
		{
			i++;
			continue ;
		}
		j = 0;
		while (argv[i][j++])
		{
			if (argv[i][j - 1] < INT_MAX[j - 1])
				break ;
			if (argv[i][j - 1] == INT_MAX[j - 1])
				continue ;
			return (1);
		}
		i++;
	}
	return (0);
}

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
	if (check_overflow(argv))
		return (1);
	return (0);
}

int	parsing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf(WRONG_N), 1);
	if (check_format(argv))
		return (printf(WRONG_F), 1);
	return (0);
}
