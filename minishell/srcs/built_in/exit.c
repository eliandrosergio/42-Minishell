/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:48 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell_component(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->envp_cpy)
		free_array((*shell)->envp_cpy);
	if ((*shell)->home_parent_shell)
		free((*shell)->home_parent_shell);
	if ((*shell)->saved_pwd)
		free((*shell)->saved_pwd);
}

void	kill_processes(t_shell **shell)
{
	t_cmd	*cmd;

	if (!shell || !*shell || (*shell)->status != INTERNAL_ERROR
		|| !(*shell)->process_level)
		return ;
	cmd = (*shell)->commands;
	while (cmd)
	{
		if (cmd->exec & PROCESS_FORKED && kill(cmd->pid, SIGKILL) == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		cmd = cmd->next;
	}
}

void	built_in_exit(t_shell **shell)
{
	int		exit_status;
	t_list	*arg;

	if (!shell || !*shell)
		exit(1);
	exit_status = get_exit_status(shell);
	arg = built_in_exit_fetch_arg(shell);
	if (arg)
	{
		if (!built_in_exit_within_range(shell, arg->name, &exit_status))
			if (shell && *shell)
				error_handler(shell, arg->name, 255, "num arg requer");
		if (arg->next && exit_status != 255)
		{
			if (shell && *shell)
				error_handler(shell, NULL, 1, "too many arguments");
			return ;
		}
	}
	clear_history();
	kill_processes(shell);
	reset_shell(shell);
	free_shell_component(shell);
	*shell = NULL;
	exit(exit_status);
}

t_list	*built_in_exit_fetch_arg(t_shell **shell)
{
	t_list	*curr_arg;

	if (!shell || !*shell || !(*shell)->current_command)
		return (NULL);
	curr_arg = (*((*shell)->current_command))->args;
	if (curr_arg && match_str("exit", curr_arg->name, 1))
	{
		if (!((*((*shell)->current_command))->exec & PROCESS_FORKED))
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (curr_arg->next);
	}
	return (NULL);
}

bool	built_in_exit_within_range(t_shell **shell,
	char *exit_arg, int *exit_status)
{
	int	i;

	if (!exit_arg || !exit_status)
		return (false);
	i = 0;
	while (exit_arg[i])
	{
		if ((exit_arg[i] == '+' || exit_arg[i] == '-') && i == 0)
			i++;
		else if (!isdigit(exit_arg[i]))
		{
			*exit_status = 2;
			if (shell && *shell)
				error_handler(shell, exit_arg, 2, "requer argumento numérico");
			return (false);
		}
		else
			i++;
	}
	*exit_status = ft_atoi(exit_arg);
	if (*exit_status < 0 || *exit_status > 255)
		if (shell && *shell)
			error_handler(shell, exit_arg, 255, "out of range");
	return (true);
}
