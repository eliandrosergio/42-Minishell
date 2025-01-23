/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/23 12:03:46 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_bin_based_on_path(char *bin_route, t_shell *shell, t_cmd *cmd)
{
	struct stat	buf;
	char		*tmp;
	char		**path;
	int			i;

	i = -1;
	tmp = ft_getenv("PATH", &shell->envp_list);
	path = ft_split(tmp, ':');
	while (path[++i] != NULL)
	{
		buf.st_mode = 0;
		tmp = ft_strjoin(path[i], "/");
		bin_route = ft_strjoin(tmp, cmd->cmd);
		stat(bin_route, &buf);
		free(tmp);
		if (access(bin_route, F_OK) == 0 && !S_ISDIR(buf.st_mode))
			ft_free_args(path);
		if (access(bin_route, F_OK) == 0 && !S_ISDIR(buf.st_mode))
			return (bin_route);
		if (bin_route != NULL)
			free(bin_route);
	}
	ft_free_args(path);
	return (ft_strdup(cmd->cmd));
}

void	ft_exec_on_path(t_shell *shell, t_cmd *cmd)
{
	char	*tmp;
	char	*bin_route;

	bin_route = NULL;
	if (access(cmd->cmd, F_OK) == 0)
		bin_route = ft_strdup(cmd->cmd);
	else
	{
		tmp = ft_getenv("PATH", &shell->envp_list);
		if (tmp == NULL)
		{
			ft_putstr_fd("minishell: \n", 2);
			ft_putstr_fd(cmd->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free_all(shell, true, false);
			exit(127);
		}
		bin_route = ft_get_bin_based_on_path(bin_route, shell, cmd);
	}
	ft_execve(bin_route, cmd->args, shell->envp, shell);
	if (bin_route != NULL)
		free(bin_route);
}

bool	is_builtin(char *cmd, char *builtin)
{
	return (ft_strlen(cmd) == ft_strlen(builtin)
		&& ft_strcmp(cmd, builtin) == 0);
}

int	ft_exec_on_parent(t_cmd *cmd, t_shell *shell)
{
	int	workdone;

	workdone = -1;
	if (is_builtin(cmd->cmd, "exit"))
		workdone = ft_exit(shell, !ft_is_pipe(shell->line));
	else if (is_builtin(cmd->cmd, "cd"))
		workdone = ft_cd(cmd, shell);
	else if (is_builtin(cmd->cmd, "export"))
		workdone = ft_export(cmd, shell);
	else if (is_builtin(cmd->cmd, "unset"))
		workdone = ft_unset(cmd, shell);
	shell->status = ft_crtl_c(workdone);
	return (workdone);
}

int	ft_exec_on_builtin(t_cmd *cmd, t_shell *shell)
{
	int	workdone;

	workdone = -1;
	if (is_builtin(cmd->cmd, "exit"))
		workdone = ft_exit(shell, !ft_is_pipe(shell->line));
	else if (is_builtin(cmd->cmd, "cd"))
		workdone = ft_cd(cmd, shell);
	else if (is_builtin(cmd->cmd, "pwd"))
		workdone = ft_pwd();
	else if (is_builtin(cmd->cmd, "export"))
		workdone = ft_export(cmd, shell);
	else if (is_builtin(cmd->cmd, "unset"))
		workdone = ft_unset(cmd, shell);
	else if (is_builtin(cmd->cmd, "env"))
		workdone = ft_env(shell);
	else if (is_builtin(cmd->cmd, "echo"))
		workdone = ft_echo(cmd);
	shell->status = ft_crtl_c(workdone);
	return (workdone);
}
