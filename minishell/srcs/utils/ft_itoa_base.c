/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:37:26 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_char(int *value, int base)
{
	int	i;
	int	new_value;

	i = 0;
	new_value = *value;
	if ((*value) < 0)
	{
		(*value) *= -1;
		new_value = *value;
		i++;
	}
	while (new_value > 0)
	{
		i++;
		new_value = new_value / base;
	}
	if (!i)
		i = 1;
	return (i);
}

char	*ft_itoa_base(int value, int base)
{
	int			i;
	char		negative;
	char		*result;
	static char	b[16] = "0123456789ABCDEF";

	if (base < 2 || base > 16)
		return (0);
	negative = value < 0;
	i = get_nb_char(&value, base);
	result = malloc((i + 1) * sizeof(char));
	result[i] = '\0';
	while (value >= base)
	{
		i--;
		result[i] = b[value % base];
		value /= base;
	}
	if (negative)
	{
		result[1] = b[value % base];
		result[0] = '-';
	}
	else
		result[0] = b[value % base];
	return (result);
}
