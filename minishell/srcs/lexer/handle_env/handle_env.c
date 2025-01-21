/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 13:53:06 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env(t_shell **shell, char **input, int *i,
		unsigned char *parse)
{
	if (*parse & LEXER)
		handle_env_lexer_level(shell, input, i);
	else
		handle_env_exec_level(shell, input, i, parse);
	if ((*shell)->current_status != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

void	handle_env_lexer_level(t_shell **shell, char **input, int *i)
{
	int	index;

	index = *i;
	get_offset(shell, input, index, i);
	if (*i != index)
		(*i)--;
}

void	handle_env_exec_level(t_shell **shell, char **input, int *i,
		unsigned char *parse)
{
	if (!((*parse & QUOTED_DOUBLE) && ((*input)[*i + 1] == '"')))
		integrate_env(input, i, shell);
	if ((*shell)->current_status == IGN_ENV_SUB)
		(*shell)->current_status = SUCCESS;
}
