/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exec_relative_path(t_shell **shell)
{
	char	*full_path;
	char	*exec_name;
	char	next;
	int		i;

	full_path = check_exec_copy_path(shell);
	exec_name = check_exec_get_exec_name(shell, &full_path);
	i = 0;
	while (full_path[i])
	{
		if ((*shell)->absolute_path)
			check_exec_free(shell, NULL, NULL);
		next = update_current_path(shell, &full_path, &exec_name, &i);
		if (stat((*shell)->absolute_path, &((*shell)->statbuf)) == 0)
		{
			check_exec_free(NULL, &full_path, &exec_name);
			return ;
		}
		if (next)
			i++;
	}
	check_exec_free(shell, &full_path, &exec_name);
	(*((*shell)->current_command))-> exec |= PROCESS_NOT_FOUND;
	error_handler(shell, NULL, CMD_NOT_FOUND, ERR_CMD_NOT_FOUND);
	return ;
}

void	check_exec_absolute_path(t_shell **shell)
{
	if (stat((*((*shell)->current_command))->name, &((*shell)->statbuf)) == 0)
	{
		if (((*shell)->statbuf.st_mode & S_IFMT) == S_IFDIR)
		{
			error_handler(shell, NULL, EXEC_FAILURE, strerror(EISDIR));
			(*((*shell)->current_command))->exec |= PROCESS_NOT_EXEC;
		}
		return ;
	}
	if (errno == ENOENT)
	{
		error_handler(shell, NULL, CMD_NOT_FOUND, strerror(errno));
		(*((*shell)->current_command))->exec |= PROCESS_NOT_FOUND;
	}
	else
	{
		error_handler(shell, NULL, EXEC_FAILURE, strerror(errno));
		(*((*shell)->current_command))->exec |= PROCESS_NOT_EXEC;
	}
}
