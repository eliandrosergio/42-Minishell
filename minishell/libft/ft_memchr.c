/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:33:38 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 19:33:41 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*converted_b;

	converted_b = (unsigned char *) b;
	while (len--)
	{
		if (*converted_b == (unsigned char) c)
			return ((void *)converted_b);
		converted_b++;
	}
	return (NULL);
}
