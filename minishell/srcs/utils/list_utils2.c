/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_current(t_list ***current, t_list **node)
{
	if (*node)
	{
		(*(*current))->next = *node;
		*current = node;
	}
}

void	update_node(t_shell **shell, t_list **node, char *token)
{
	(*node) = new_node(shell, token, NOT_ASSIGNED);
	(*node)->token_type = EXPANDED_TOKEN;
}

void	update_list(t_shell **shell, t_list **list, char *token,
		t_list ***current)
{
	*list = new_node(shell, token, NOT_ASSIGNED);
	(*list)->token_type = EXPANDED_TOKEN;
	*current = list;
}
