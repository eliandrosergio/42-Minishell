/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:48:43 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return ;
	while (i < n)
	{
		*(((char *)s) + i) = 0;
		i++;
	}
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*((char *)(dst + i)) = *((const char *)(src + i));
		i++;
	}
	return (dst);
}

void	indexing(char **line, char **valid_escape_char, int *index)
{
	*index = 0;
	while (valid_escape_char[*index])
	{
		if (match_str(*line, valid_escape_char[*index], 0))
			break ;
		(*index)++;
	}
}

void	iter_whitespaces(char **line, int *index)
{
	while (index && (*line)[*index] &&
			((*line)[*index] == ' ' || (*line)[*index] == '\t'))
		(*index)++;
	while (!index && line && *line && **line
		&& (**line == ' ' || **line == '\t'))
		(*line)++;
}
