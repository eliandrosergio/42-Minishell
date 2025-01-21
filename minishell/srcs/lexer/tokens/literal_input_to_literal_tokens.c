/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_input_to_literal_tokens.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_literal_tokens(char **input, t_shell **shell)
{
	int		tokens;
	char	**literal_tokens;

	tokens = n_tokens(*input);
	literal_tokens = (char **)(malloc((tokens + 1) * sizeof(char *)));
	if (!literal_tokens)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	literal_tokens[tokens] = NULL;
	if ((*shell)->tokens_info)
		free((*shell)->tokens_info);
	(*shell)->tokens_info = malloc((tokens + 1) * sizeof(char));
	(*shell)->current_n_tokens = tokens;
	if (!(*shell)->tokens_info)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	ft_bzero((*shell)->tokens_info, tokens + 1);
	fill_tokens(literal_tokens, *input, shell);
	return (literal_tokens);
}

void	fill_tokens(char **literal_tokens, char *input, t_shell **shell)
{
	int		i;
	int		token;
	int		trim;

	i = 0;
	token = 0;
	while (input[i])
	{
		iter_whitespaces(&input, &i);
		trim = trim_words(input + i);
		if (!trim)
			break ;
		literal_tokens[token] = new_literal_token(shell, trim, input + i);
		if (!literal_tokens[token])
			error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
		((*shell)->tokens_info)[token] = 1;
		if (literal_tokens[token][0] == '"'
				|| literal_tokens[token][0] == '\''
				|| is_escaped_meta_token(literal_tokens[token]))
			((*shell)->tokens_info)[token] |= QUOTED;
		token++;
		i += trim;
	}
}

char	*new_literal_token(t_shell **shell, int len, char *token)
{
	char	*new;

	new = malloc((len + 1) * sizeof(char));
	if (!new)
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	ft_memcpy(new, token, len);
	new[len] = '\0';
	return (new);
}

int	parse_meta_token(char *line, int i)
{
	if (line[i + 1] && ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<')))
		return (i + 2);
	return (i + 1);
}

void	set_literal(char *line, unsigned char *parse)
{
	if (match_str(line, "\\|", 0))
		*parse |= LITERAL_PIPE;
	if (match_str(line, "\\>", 0) || match_str(line, "\\<", 0))
		*parse |= LITERAL_REDIR;
	if (match_str(line, "\\;", 0))
		*parse |= LITERAL_SEMICOLON;
	if (match_str(line, "\\ ", 0))
		*parse |= LITERAL_WHITESPACE;
	if (match_str(line, "\\\"", 0))
		*parse |= LITERAL_QUOTE;
	if (match_str(line, "\\'", 0))
		*parse |= LITERAL_QUOTE;
}
