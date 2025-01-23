/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:10:29 by antonfer          #+#    #+#             */
/*   Updated: 2025/01/23 12:01:21 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse_redir_and_set_fd(char *line, t_fd *fds, t_shell *shell)
{
	int	i;

	i = -1;
	ft_init_fd(fds);
	while (line[++i] != '\0')
	{
		if (line[i] == '>')
		{
			ft_reset_fd_out(fds);
			ft_open_file(line, i, fds, shell);
			if (line[i + 1] == '>')
				i++;
		}
		else if (line[i] == '<')
		{
			ft_reset_fd_in(fds);
			ft_open_file(line, i, fds, shell);
			if (shell->heredoc_exitstatus == 130)
				return ;
			if (line[i + 1] == '<')
				i++;
		}
		else if (line[i] == '\'' || line[i] == '\"')
			i = ft_skiptochr(line, i + 1, line[i]);
	}
}

void	add_args_and_output(t_cmd *new, char **args, t_fd *fds)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	new->argc = i;
	new->args = ft_matdup(args);
	new->fd.fd_in = fds->fd_in;
	new->fd.fd_out = fds->fd_out;
	new->fd.filename_in = fds->filename_in;
	new->fd.filename_out = fds->filename_out;
}

void	add_cmd(t_shell *shell, char **args, t_fd *fds, int is_pipe)
{
	t_cmd	*new;
	t_cmd	*last;

	if (args != NULL && args[0] == NULL)
		return ;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->cmd = ft_strdup(args[0]);
	if (is_pipe == 1)
		new->type = PIPE;
	else
		new->type = EXEC;
	add_args_and_output(new, args, fds);
	if (shell->cmd == NULL)
		shell->cmd = new;
	else
	{
		last = shell->cmd;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

int	ft_free_mat(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL)
		return (1);
	while (mat[i] != NULL)
		free(mat[i++]);
	free(mat);
	mat = NULL;
	return (1);
}

void	parse_line(t_shell *shell)
{
	char	**args;
	t_fd	fds;
	int		i;
	int		j;

	i = -1;
	if (ft_check_unvalid(shell->line) == 1)
		return ;
	shell->cmdstmp = ft_parser_split(shell->line, "|");
	while (shell->cmdstmp[++i] != NULL)
	{
		ft_parse_redir_and_set_fd(shell->cmdstmp[i], &fds, shell);
		if (shell->heredoc_exitstatus == 130 && ft_free_mat(shell->cmdstmp))
			return ;
		ft_expand_sign_matrix(&shell->cmdstmp[i], shell, 0);
		args = ft_parser_split(shell->cmdstmp[i], " \t");
		j = -1;
		while (args[++j] != NULL)
			ft_remove_quotes_logic(args[j], ft_strlen(args[j]));
		add_cmd(shell, args, &fds, ft_is_pipe(shell->line));
		ft_free_args(args);
	}
	ft_free_args(shell->cmdstmp);
	shell->cmdstmp = NULL;
}
