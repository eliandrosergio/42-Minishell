/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 10:13:32 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_export(t_shell **shell)
{
	t_list	*arg;

	arg = (*((*shell)->current_command))->args->next;
	if (!arg)
		built_in_export_no_arg(shell);
	else if (*(arg->name) == '-')
	{
		error_handler(shell, arg->name, ERROR, ERR_NO_OPT);
		return ;
	}
	else
	{
		while (arg)
		{
			built_in_export_with_arg(shell, arg->name, 0);
			arg = arg->next;
		}
	}
}

void	built_in_export_no_arg(t_shell **shell)
{
	int		env;
	char	**envp_sorted;

	envp_sorted = copy_array(shell, (*shell)->envp_cpy, (*shell)->n_env);
	sort_env(envp_sorted, 0, (*shell)->n_env);
	env = 0;
	while (envp_sorted[env])
	{
		built_in_export_print(envp_sorted[env]);
		env++;
	}
	free_array(envp_sorted);
}

void	built_in_export_print(char *envp)
{
	int		i;

	i = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (envp[i] && envp[i] != '=')
	{
		write(STDOUT_FILENO, &envp[i], 1);
		i++;
	}
	if (envp[i])
	{
		write(STDOUT_FILENO, "=\"", 2);
		i++;
		built_in_export_display_env(envp + i);
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int	built_in_export_with_arg(t_shell **shell, char *arg, int internal)
{
	int	env;
	int	match;

	env = 0;
	match = 0;
	if (!built_in_export_valid_identifier(arg))
	{
		error_handler(shell, arg, ERROR, "not a valid identifier");
		return (ERROR);
	}
	while ((*shell)->envp_cpy[env] && !match)
	{
		match = match_env((*shell)->envp_cpy[env], arg);
		env++;
	}
	if (!match)
		return (push_env(shell, arg, internal));
	return (change_env(shell, &(*shell)->envp_cpy[env - 1], arg, internal));
}

bool	built_in_export_valid_identifier(const char *arg)
{
	int	i;

	i = 1;
	if (ft_isalnum(arg[0]) != 1 && arg[0] != '_')
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
