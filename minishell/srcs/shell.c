/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:35:58 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	run_shell(t_shell **shell)
{
	char	*input;

	input = NULL;
	while ((*shell)->current_status != INTERNAL_ERROR)
	{
		reset_shell(shell);
		shell_signals(shell);
		if (g_signal)
			g_signal = 0;
		input = prompt();
		if (g_signal)
		{
			(*shell)->status = g_signal;
			g_signal = 0;
		}
		if (input && *input)
			add_history(input);
		lexer(shell, &input);
		parser(shell);
		if ((*shell)->current_status == SUCCESS)
			exec_cmd_line(shell);
		update_status(shell);
	}
}

char	*prompt(void)
{
	char	*input;

	input = readline("minishell$> ");
	if (!input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	return (input);
}

void	update_status(t_shell **shell)
{
	if ((*shell)->current_status == SHELL_ERROR
		|| (*shell)->current_status == BAD_SUBSTITUTION
		|| (*shell)->current_status == NO_OPT
		|| (*shell)->current_status == NO_ARG
		|| (*shell)->current_status == AMBIGUOUS_REDIRECT)
		(*shell)->status = ERROR;
	else if ((*shell)->current_status == NO_MULTI_LINE)
		(*shell)->status = 2;
	else
		(*shell)->status = (*shell)->current_status;
}
