/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:04:11 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 20:04:12 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	ft_size(size_t str_len, size_t start, size_t max_len)
{
	unsigned int	holder;

	if (start < str_len)
	{
		holder = str_len - start;
	}
	if (start >= str_len)
	{
		holder = 0;
	}
	if (holder > max_len)
	{
		holder = max_len;
	}
	return (holder);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring_ptr;
	unsigned int	new_max_len;
	size_t			str_len;

	if (!s)
		return (NULL);
	str_len = (unsigned int) ft_strlen(s);
	new_max_len = ft_size(str_len, start, len);
	if (new_max_len == 0)
		return (ft_strdup(""));
	substring_ptr = ft_calloc(new_max_len + 1, sizeof(char));
	if (!substring_ptr)
		return (NULL);
	ft_strlcpy (substring_ptr, &s[start], new_max_len + 1);
	return (substring_ptr);
}
