/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(t_shell **shell, char **src, int size)
{
	int		i;
	int		len;
	char	**dst;

	i = 0;
	dst = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	while (src[i])
	{
		len = str_len(src[i], NULL, 0);
		dst[i] = ft_join(src[i], NULL, len);
		if (!dst[i])
		{
			free_array(dst);
			error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}
