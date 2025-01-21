/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_literal_tokens_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 12:25:26 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_tokens(char *line)
{
	int		i;
	int		tokens;
	int		trim;

	tokens = 0;
	i = 0;
	while (line[i])
	{
		trim = trim_words(line + i);
		if (!trim)
			break ;
		i += trim;
		tokens++;
	}
	return (tokens);
}

bool	is_escaped_meta_token(char *token)
{
	return (match_str("\\>", token, 1)
		|| match_str("\\>\\>", token, 1)
		|| match_str("\\<", token, 1)
		|| match_str("\\;", token, 1)
		|| match_str("\\|", token, 1));
}
