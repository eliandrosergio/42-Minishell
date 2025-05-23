/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:10:29 by antonfer          #+#    #+#             */
/*   Updated: 2025/01/23 12:01:21 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_handle_output(char *line, int i, t_fd *fds, t_shell *shell)
{
	line[i] = ' ';
	if (line[i + 1] == '>')
	{
		line[i + 1] = ' ';
		fds->filename_out = ft_strchr_dupfilename(line, i + 2, shell, true);
		if (fds->filename_out != NULL)
			fds->fd_out = open(fds->filename_out, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			fds->fd_out = -1;
	}
	else
	{
		fds->filename_out = ft_strchr_dupfilename(line, i + 1, shell, true);
		if (fds->filename_out != NULL)
			fds->fd_out = open(fds->filename_out, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else
			fds->fd_out = -1;
	}
}

static void	ft_handle_input(char *line, int i, t_fd *fds, t_shell *shell)
{
	line[i] = ' ';
	if (line[i + 1] == '<')
	{
		line[i + 1] = ' ';
		fds->fd_heredoc = 1;
		fds->filename_in = ft_strchr_dupfilename(line, i + 2, shell, false);
		ft_heredoc_handler(fds, shell);
		if (shell->heredoc_exitstatus == 130)
		{
			free(fds->filename_in);
			return ;
		}
	}
	else
	{
		fds->fd_heredoc = 0;
		fds->filename_in = ft_strchr_dupfilename(line, i + 1, shell, true);
		if (fds->filename_in != NULL)
			fds->fd_in = open(fds->filename_in, O_RDONLY);
		else
			fds->fd_in = -1;
	}
}

void	ft_open_file(char *line, int i, t_fd *fds, t_shell *shell)
{
	if (line[i] == '>')
		ft_handle_output(line, i, fds, shell);
	else if (line[i] == '<')
		ft_handle_input(line, i, fds, shell);
}
