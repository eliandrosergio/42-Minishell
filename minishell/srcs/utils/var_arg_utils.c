/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:44:22 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_args_loop_expand(t_shell **shell, t_list **tmp)
{
	if (!*tmp)
		return ;
	if ((*tmp)->token_type == LITERAL_TOKEN)
		cmd_args_var_expansion(shell);
}

void	cmd_args_update_current_arg_int(t_shell **shell, t_list ***tmp)
{
	(*((*shell)->current_command))->current_arg = &((*(*tmp))->next);
	free((**tmp));
	**tmp = *((*((*shell)->current_command))->current_arg);
}

void	cmd_args_push_arg_list(t_shell **shell, char **interpreted_result,
		t_list ***tmp)
{
	int		arg;
	t_list	*list;
	t_list	*node;
	t_list	**end;

	arg = 1;
	list = NULL;
	node = NULL;
	end = NULL;
	while (interpreted_result[arg])
	{
		if (list)
			update_node(shell, &node, interpreted_result[arg]);
		else
			update_list(shell, &list, interpreted_result[arg], &end);
		update_current(&end, &node);
		arg++;
	}
	(*((*shell)->current_command))->n_args += arg;
	cmd_args_sync_name(shell, tmp, interpreted_result[0]);
	cmd_args_push_update(&list, end, tmp);
}

void	cmd_args_sync_name(t_shell **shell, t_list ***tmp, char *name)
{
	(*((*shell)->current_command))->current_arg = *tmp;
	(*((*((*shell)->current_command))->current_arg))->name = name;
	(*((*((*shell)->current_command))->current_arg))->token_type
		= EXPANDED_TOKEN;
}

void	cmd_args_push_update(t_list **list, t_list **end,
		t_list ***tmp)
{
	if (*list)
		push_to_list(*tmp, *list);
	if (end)
		*tmp = &((*end)->next);
	else
		*tmp = &((*(*tmp))->next);
}
