/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 10:44:46 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_shell **shell, t_list **current, int *tmp_fd)
{
	if (pipe((*shell)->filedes) == -1)
		error_handler(shell, NULL, INTERNAL_ERROR, strerror(errno));
	if ((*((*shell)->current_command))->out == NOT_ASSIGNED)
	{
		if (close(tmp_fd[OUT]) == -1)
			error_handler(shell, (*current)->name, ERROR, strerror(errno));
		tmp_fd[OUT] = (*shell)->filedes[OUT];
	}
	else
	{
		if (close((*shell)->filedes[OUT]) == -1)
			error_handler(shell, (*current)->name, ERROR, strerror(errno));
	}
	tmp_fd[IN] = (*shell)->filedes[IN];
	if ((*((*shell)->current_command))->out != NOT_ASSIGNED)
		(*((*shell)->current_command))->separator = SEMICOLON;
	(*((*shell)->current_command))->exec |= PROCESS_PIPED;
	if ((*((*shell)->current_command))->next)
		(*((*shell)->current_command))->next->exec |= PROCESS_PIPED;
}

int	handle_semicolon(t_shell **shell, t_cmd **current,
							t_cmd **wait_start)
{
	if ((*current)->separator == SEMICOLON)
	{
		wait_and_signal_check(shell, *wait_start);
		*wait_start = (*current)->next;
		if ((*shell)->current_status == PARSING_ERROR
			|| (*shell)->current_status == BAD_SUBSTITUTION
			|| (*shell)->current_status == NO_MULTI_LINE)
			return (ERROR);
		update_status(shell);
	}
	return (SUCCESS);
}
