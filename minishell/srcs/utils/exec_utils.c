/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 11:55:38 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_and_close(t_shell **shell, int fd, int stdio)
{
	if (dup2(fd, stdio) == -1)
		error_handler(shell, NULL, INTERNAL_ERROR, strerror(errno));
	if (close(fd) == -1)
		error_handler(shell, NULL, INTERNAL_ERROR, strerror(errno));
}

int	open_file(t_shell **shell, t_list **current, int *fd, int mode)
{
	if (mode)
		*fd = open((*current)->name, (*current)->value, 0644);
	else
		*fd = open((*current)->name, (*current)->value);
	if (*fd == -1)
	{
		error_handler(shell, (*current)->name, SHELL_ERROR, strerror(errno));
		return (ERROR);
	}
	return (SUCCESS);
}
