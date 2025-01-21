/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void	shell_signals(t_shell **shell)
{
	if (signal(SIGQUIT, shell_signal_handler) == SIG_ERR)
		built_in_exit(shell);
	if (signal(SIGINT, shell_signal_handler) == SIG_ERR)
		built_in_exit(shell);
}

void	shell_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		prompt();
		g_signal = TERM_C;
	}
	else if (signal == SIGQUIT)
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
}

void	exec_signals(t_shell **shell)
{
	if (signal(SIGQUIT, exec_signal_handler) == SIG_ERR)
		built_in_exit(shell);
	if (signal(SIGINT, exec_signal_handler) == SIG_ERR)
		built_in_exit(shell);
}

void	exec_signal_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	if (signal == SIGINT)
	{
		g_signal = TERM_C;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	wait_and_signal_check(t_shell **shell, t_cmd *current)
{
	int			w_status;

	w_status = 0;
	while (current)
	{
		if (current->exec & PROCESS_NOT_EXEC)
			(*shell)->current_status = EXEC_FAILURE;
		else if (current->exec & PROCESS_NOT_FOUND)
			(*shell)->current_status = CMD_NOT_FOUND;
		else if (current->exec & PROCESS_FORKED)
		{
			waitpid(current->pid, &w_status, WUNTRACED);
			if (WIFSIGNALED(w_status))
				(*shell)->current_status = 128 + WTERMSIG(w_status);
			else if (WIFEXITED(w_status))
				(*shell)->current_status = WEXITSTATUS(w_status);
		}
		if (current->separator == SEMICOLON)
			break ;
		current = current->next;
	}
}
