/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:53:02 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/07 15:12:45 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_isdigit(int i)
{
	if (47 < i && i < 58)
		return (1);
	return (0);
}

static size_t	_get_real_size(const char *str, size_t *i)
{
	size_t	count;
	size_t	j;

	*i = 0;
	while (str[*i] == '0')
		(*i)++;
	count = 0;
	j = *i;
	while (str[j] && ft_isdigit(str[j]))
	{
		count++;
		j++;
	}
	return (count);
}

static int	_is_bigger(const char *str, size_t i, int is_negative)
{
	char	*ll_max;
	size_t	j;

	j = 0;
	ll_max = "9223372036854775807";
	while (str[i] && ll_max[j])
	{
		if (str[i] < ll_max[j])
			return (1);
		if (str[i] > ll_max[j])
		{
			if (is_negative)
				return (0);
			return (-1);
		}
		i++;
		j++;
	}
	if (is_negative)
		return (1);
	return (-1);
}

static int	_check_overflow(const char *str, int is_negative)
{
	size_t		i;
	size_t		real_size;

	real_size = _get_real_size(str, &i);
	if ((real_size > 19 && is_negative) || !str[i])
		return (0);
	if (real_size > 19 && !is_negative)
		return (-1);
	if (real_size == 19)
		return (_is_bigger(str, i, is_negative));
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		nbr_is_negative;
	int		result;

	nbr_is_negative = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			nbr_is_negative = 1;
	result = _check_overflow(str + i, nbr_is_negative);
	if (result < 1)
		return (result);
	result = 0;
	while (str[i] && '0' <= str[i] && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	if (nbr_is_negative)
		result = (long)result * -1;
	return (result);
}