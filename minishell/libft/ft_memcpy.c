/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:06:32 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 17:06:33 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*memory_src;
	unsigned char	*memory_dst;
	unsigned int	counter;

	if (src == NULL && dst == NULL)
		return (dst);
	memory_src = (unsigned char *)src;
	memory_dst = (unsigned char *)dst;
	counter = 0;
	while (len > counter)
	{
		memory_dst[counter] = memory_src[counter];
		counter++;
	}
	return (dst);
}
