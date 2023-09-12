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

int	check_format(char **argv)
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

t_data	*get_params(int argc, char **argv)
{
	t_data	*params;

	params = malloc(sizeof(t_data));
	if (!params)
		return (NULL);
	params->phil_nb = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	if (argc < 5)
		params->eat_limit = ft_atoi(argv[5]);
	else
		params->eat_limit = -1;
	return (params);
}

t_data	*parsing(int argc, char **argv)
{
	t_data	*params;

	if (argc < 5 || argc > 6)
		return (printf(WRONG_ARG), NULL);
	if (check_format(argv))
		return (printf(WRONG_F), NULL);
	params = get_params(argc, argv);
	return (params);
}
