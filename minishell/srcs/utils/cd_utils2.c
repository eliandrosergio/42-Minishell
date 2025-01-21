/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:43:16 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_paths(char **new_path, char **new_path_tmp, char **dot_sub_path,
		char *dir)
{
	if (new_path)
	{
		free(*new_path);
		*new_path = NULL;
	}
	if (new_path_tmp)
	{
		free(*new_path_tmp);
		*new_path_tmp = NULL;
	}
	if (dot_sub_path)
	{
		free(*dot_sub_path);
		*dot_sub_path = NULL;
	}
	if (dir)
	{
		free(dir);
		dir = NULL;
	}
	return (1);
}

char	*create_tmp_path(t_shell **shell, char **new_path, size_t new_path_len,
		char *dir)
{
	char	*tmp_path;

	tmp_path = ft_join(*new_path, NULL, new_path_len);
	if (!tmp_path)
	{
		free_paths(new_path, NULL, NULL, dir);
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	}
	return (tmp_path);
}
