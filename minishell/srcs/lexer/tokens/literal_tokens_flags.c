/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_tokens_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 13:58:58 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flag_literal_bslash(unsigned char *parse, unsigned char *delete)
{
	if (!(*parse & QUOTED_SINGLE))
		*delete = 1;
	*parse |= LITERAL_BACKSLASH;
}

void	flag_literal_env(unsigned char *parse, unsigned char *delete)
{
	if (!(*parse & QUOTED_SINGLE))
		*delete = 1;
	*parse |= LITERAL_ENV;
}

void	flag_bslash_term(t_shell **shell, unsigned char *delete)
{
	(*shell)->current_status = BACKSLASH_TERM;
	*delete = 1;
}

void	flag_literal_quote(unsigned char *parse, unsigned char *delete,
		char to_escape)
{
	if (*parse & QUOTED_DOUBLE)
	{
		*delete = to_escape == '"';
		*parse |= LITERAL_QUOTE;
	}
	else if (!(*parse & QUOTED_SINGLE))
	{
		*delete = 1;
		*parse |= LITERAL_QUOTE;
	}
}

void	flag_quotes(int n_quotes, t_shell **shell)
{
	if (n_quotes % 2)
	{
		(*shell)->current_status = NO_MULTI_LINE;
		error_handler(shell, NULL, NO_MULTI_LINE, ERR_MULTI_LINE);
	}
}
