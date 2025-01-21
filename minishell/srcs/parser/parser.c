/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 11:12:43 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_shell **shell)
{
	int	i;

	i = 0;
	while ((*shell)->current_status == SUCCESS && (*shell)->tokens[i])
	{
		if (init_cmd(shell, (*shell)->tokens[i], &i) != SUCCESS)
			return ;
		if (parse_tokens(shell, (*shell)->current_command, &i) != SUCCESS)
			return ;
	}
}

int	init_cmd(t_shell **shell, char *cmd_name, int *i)
{
	int	meta;

	meta = meta_to_code(cmd_name);
	if (meta == PIPE || meta == SEMICOLON)
	{
		error_handler(shell, NULL, PARSING_ERROR, ERR_PARSE);
		return (ERROR);
	}
	else if (meta < SEMICOLON)
	{
		push_command(shell, NULL, *i);
		(*shell)->current_n_tokens++;
		return (SUCCESS);
	}
	push_command(shell, cmd_name, *i);
	push_cmd_arg(shell, cmd_name, i);
	return (SUCCESS);
}

int	parse_tokens(t_shell **shell, t_cmd **current, int *i)
{
	int	meta;

	while ((*shell)->tokens[*i] && (*shell)->current_status == SUCCESS)
	{
		if (is_meta_token(shell, *i))
			meta = meta_to_code((*shell)->tokens[*i]);
		else
			meta = NOT_ASSIGNED;
		if (meta <= REDIR_INPUT)
		{
			if (assign_io(shell, current, meta, i) != SUCCESS)
				return (ERROR);
		}
		else if (meta <= PIPE)
			break ;
		else
		{
			if (!(*current)->name)
				(*((*shell)->current_command))->name = (*shell)->tokens[*i];
			push_cmd_arg(shell, (*shell)->tokens[*i], i);
		}
	}
	if (check_if_separator(shell, current, i, meta) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	assign_io(t_shell **shell, t_cmd **current,
					int meta, int *i)
{
	char	*file_name;

	file_name = (*shell)->tokens[*i + 1];
	if (!file_name || meta_to_code(file_name) != NOT_ASSIGNED)
	{
		error_handler(shell, NULL, PARSING_ERROR, ERR_PARSE);
		return (ERROR);
	}
	if (meta == REDIR_INPUT)
		(*current)->in = REDIR_INPUT;
	else
		(*current)->out = meta;
	push_io_file(shell, meta, file_name, i);
	return (SUCCESS);
}

int	check_if_separator(t_shell **shell, t_cmd **current, int *i,
							int meta)
{
	if ((*shell)->tokens[*i] && (*shell)->current_status == SUCCESS
		&& (meta == PIPE || meta == SEMICOLON))
	{
		(*current)->separator = meta;
		(*i)++;
		if (meta == PIPE && !(*shell)->tokens[*i])
		{
			error_handler(shell, NULL, NO_MULTI_LINE, ERR_MULTI_LINE);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
