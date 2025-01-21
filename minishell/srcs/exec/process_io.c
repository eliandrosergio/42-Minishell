/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 10:25:57 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_in(t_shell **shell, int *tmp_fd, int *saved_std)
{
	t_list	**current;

	current = &((*((*shell)->current_command))->in_files);
	if (tmp_fd[IN] == saved_std[IN])
	{
		tmp_fd[IN] = dup(saved_std[IN]);
		if (tmp_fd[IN] == -1)
			error_handler(shell, NULL, INTERNAL_ERROR, strerror(errno));
	}
	while (*current)
	{
		if (close(tmp_fd[IN]) == -1)
			error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
		if (open_file(shell, current, &tmp_fd[IN], 0) == ERROR)
		{
			tmp_fd[IN] = saved_std[IN];
			return (ERROR);
		}
		current = &((*current)->next);
	}
	dup2_and_close(shell, tmp_fd[IN], STDIN_FILENO);
	tmp_fd[IN] = saved_std[IN];
	return (SUCCESS);
}

int	process_out(t_shell **shell, int *tmp_fd, int *saved_std)
{
	t_list	**current;

	tmp_fd[OUT] = dup(saved_std[OUT]);
	if (tmp_fd[OUT] == -1)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	current = &((*((*shell)->current_command))->out_files);
	while (*current)
	{
		if (close(tmp_fd[OUT]) == -1)
			error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
		if (open_file(shell, current, &tmp_fd[OUT], 1) == ERROR)
			return (ERROR);
		current = &((*current)->next);
	}
	if ((*((*shell)->current_command))->separator == PIPE)
		handle_pipe(shell, current, tmp_fd);
	dup2_and_close(shell, tmp_fd[OUT], STDOUT_FILENO);
	return (SUCCESS);
}
