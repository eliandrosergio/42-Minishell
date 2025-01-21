/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_offset2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 13:55:53 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_offset_is_option(char **lit_token, int *i, int index)
{
	return (((ft_isalnum((*lit_token)[*i]) == 2)
		|| (ft_strchr(ENV_OPT, (*lit_token)[*i])
		&& !ft_isalnum((*lit_token)[*i + 1])))
			&& *i - index == 1);
	return (false);
}

void	get_offset_skip_option(t_shell **shell, char **lit_token,
		int index, int *i)
{
	(*i)++;
	set_env_sub_error(shell, lit_token, i,
		(*shell)->parse_env & BRACKET_SUB);
	if (!((*shell)->parse_env & BRACKET_SUB) && *i - index == 1)
		get_offset_ignore_env(shell, lit_token, i, index);
}

void	get_offset_stop_parsing(t_shell **shell, char **lit_token,
		int index, int *i)
{
	set_env_sub_error(shell, lit_token, i, (*shell)->parse_env & BRACKET_SUB);
	if (!((*shell)->parse_env & BRACKET_SUB) && *i - index == 1)
		get_offset_ignore_env(shell, lit_token, i, index);
}

unsigned char	get_offset_end(t_shell **shell)
{
	if ((*shell)->current_status != SUCCESS)
		return (SUCCESS);
	if ((*shell)->parse_env & BRACKET_SUB)
		lexer_error_handler(shell, NULL, NO_MULTI_LINE, ERR_MULTI_LINE);
	return (SUCCESS);
}
