/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:10:29 by antonfer          #+#    #+#             */
/*   Updated: 2025/01/23 12:01:21 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_matdup(char **mat)
{
	char	**new;
	int		i;

	i = 0;
	if (mat == NULL)
		return (NULL);
	while (mat[i] != NULL)
		i++;
	new = (char **)ft_calloc((i + 1), sizeof(char *));
	i = -1;
	while (mat[++i] != NULL)
		new[i] = ft_strdup(mat[i]);
	new[i] = NULL;
	return (new);
}

char	**ft_parser_split(char *line, char *delim)
{
	char	**matrix;
	char	*new_line;
	int		i;

	i = -1;
	new_line = ft_strdup(line);
	if (new_line == NULL)
		return (NULL);
	while (new_line[++i] != '\0')
	{
		if (new_line[i] == '\"')
			i = ft_skiptochr(new_line, ++i, '\"');
		else if (new_line[i] == '\'')
			i = ft_skiptochr(new_line, ++i, '\'');
		else if (ft_chrcmpstr(new_line[i], delim) == 0)
			new_line[i] = -32;
	}
	matrix = ft_split(new_line, -32);
	free(new_line);
	return (matrix);
}
