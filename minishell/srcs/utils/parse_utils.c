/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 12:24:19 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_meta_token(t_shell **shell, int token)
{
	if (((*shell)->tokens_info)[token] & QUOTED)
		return (false);
	if (match_str(">", (*shell)->tokens[token], 1)
		|| match_str(">>", (*shell)->tokens[token], 1)
		|| match_str("<", (*shell)->tokens[token], 1)
		|| match_str("<<", (*shell)->tokens[token], 1)
		|| match_str(";", (*shell)->tokens[token], 1)
		|| match_str("|", (*shell)->tokens[token], 1))
		return (true);
	return (false);
}

int	meta_to_code(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUTPUT);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIR_OUTPUT_APPEND);
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_INPUT);
	if (ft_strcmp(token, ";") == 0)
		return (SEMICOLON);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	return (NOT_ASSIGNED);
}

void	push_cmd_arg(t_shell **shell, char *arg, int *i)
{
	t_list	*new;
	t_cmd	**current;

	if (!arg)
		return ;
	new = new_node(shell, arg, NOT_ASSIGNED);
	if (!((*shell)->tokens_info[*i] & IGN_ENV_SUB))
		new->token_type = INTERPRETED_TOKEN;
	current = (*shell)->current_command;
	push_to_list((*current)->current_arg, new);
	if (((*current)->args)->next)
		(*current)->current_arg = last_node(&(*current)->args);
	(*current)->n_args++;
	(*i)++;
}

void	push_io_file(t_shell **shell, int meta,
					char *file_name, int *i)
{
	t_list		*new;
	t_cmd		**current;
	static int	modes[3] = {
		O_CREAT | O_TRUNC | O_RDWR,
		O_CREAT | O_APPEND | O_RDWR,
		O_RDONLY
	};

	new = new_node(shell, file_name, modes[meta]);
	if (!((*shell)->tokens_info[*i + 1] & IGN_ENV_SUB))
		new->token_type = INTERPRETED_TOKEN;
	current = (*shell)->current_command;
	if (meta == REDIR_INPUT)
	{
		push_to_list((*current)->current_in_file, new);
		if (((*current)->in_files)->next)
			(*current)->current_in_file = last_node(&(*current)->in_files);
	}
	else
	{
		push_to_list((*current)->current_out_file, new);
		if (((*current)->out_files)->next)
			(*current)->current_out_file = last_node(&(*current)->out_files);
	}
	*i += 2;
}
