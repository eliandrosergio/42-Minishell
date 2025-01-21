/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 12:21:37 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whitespaceskip(const char *str, int *i)
{
	if (str[*i] != 32 && (str[*i] < 9 || str[*i] > 13))
		return (0);
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	return (1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			i;
	intmax_t	n;

	i = 0;
	n = 0;
	whitespaceskip(str, &i);
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (n > (INTMAX_MAX / 10) || (n == (INTMAX_MAX / 10) && (str[i] - '0')
				> INTMAX_MAX % 10))
		{
			if (sign == 1)
				return (INT_MAX);
			return (INT_MIN);
		}
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return ((int)n * sign);
}
