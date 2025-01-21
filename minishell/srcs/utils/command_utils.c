/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:50:19 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(t_shell **shell, char *name)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	new->name = name;
	new->args = NULL;
	new->current_arg = &(new->args);
	new->in_files = NULL;
	new->current_in_file = &(new->in_files);
	new->out_files = NULL;
	new->current_out_file = &(new->out_files);
	new->exec_args = NULL;
	new->n_args = 0;
	new->token_type = LITERAL_TOKEN;
	new->in = NOT_ASSIGNED;
	new->out = NOT_ASSIGNED;
	new->separator = NOT_ASSIGNED;
	new->pid = 0;
	new->exec = 0;
	new->next = NULL;
	return (new);
}

void	push_command(t_shell **shell, char *cmd_name, int token)
{
	t_cmd	*new;
	t_cmd	**current;

	new = new_command(shell, cmd_name);
	if (!((*shell)->tokens_info[token] & IGN_ENV_SUB))
		new->token_type = INTERPRETED_TOKEN;
	current = (*shell)->current_command;
	if (!*current)
		*current = new;
	else
	{
		(*current)->next = new;
		current = &((*current)->next);
	}
	(*shell)->current_command = current;
}

void	free_commands(t_shell **shell)
{
	t_cmd	*next_command;

	while ((*shell)->commands)
	{
		next_command = (*shell)->commands->next;
		if ((*shell)->commands->token_type == EXPANDED_TOKEN
			&& (*shell)->commands->name)
		{
			free((*shell)->commands->name);
			(*shell)->commands->name = NULL;
			(*shell)->commands->token_type = INTERPRETED_TOKEN;
			(*shell)->commands->args->name = NULL;
			(*shell)->commands->args->token_type = INTERPRETED_TOKEN;
		}
		free_all_lists(&((*shell)->commands));
		if ((*shell)->commands->exec_args)
			free((*shell)->commands->exec_args);
		if ((*shell)->commands)
			free((*shell)->commands);
		(*shell)->commands = next_command;
	}
}
