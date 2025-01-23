/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:50:34 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 19:50:35 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s == NULL || n <= 0)
		return (NULL);
	new = (char *)ft_calloc((n + 3), sizeof(char));
	if (new == NULL)
		return (NULL);
	while (s[i] != '\0' && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
