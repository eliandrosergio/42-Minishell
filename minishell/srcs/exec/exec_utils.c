/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/23 12:03:46 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	ft_fork(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork failed\n", 2);
		ft_free_all(shell, true, false);
		exit(2);
	}
	return (pid);
}

void	ft_execve(char *bin, char **args, char **env, t_shell *shell)
{
	if (execve(bin, args, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_all(shell, true, false);
		if (bin != NULL)
			free(bin);
		exit(127);
	}
}

void	ft_dup2_errors(char *filename, t_shell *shell)
{
	struct stat	buf;

	if (filename != NULL)
	{
		buf.st_mode = 0;
		stat(filename, &buf);
		ft_putstr_fd("minishell: ", 2);
		if (filename != NULL)
			ft_putstr_fd(filename, 2);
		if (S_ISDIR(buf.st_mode))
			ft_putstr_fd(": is a directory\n", 2);
		else if (access(filename, F_OK))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (filename != NULL)
			ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	ft_free_all(shell, true, false);
	exit(1);
}

void	ft_dup2(int fd, int fd2, t_shell *shell, char *filename)
{
	if (fd == -1)
		ft_dup2_errors(filename, shell);
	if (dup2(fd, fd2) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", 2);
		ft_free_all(shell, true, false);
		exit(2);
	}
}

void	ft_signal_hand(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
