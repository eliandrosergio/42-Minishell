/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_shell **shell, char **input)
{
	char	**literal_tokens;
	char	**interpreted_tokens;

	literal_tokens = NULL;
	interpreted_tokens = NULL;
	input_to_literal_input(shell, input, LEXER);
	if ((*shell)->current_status == SUCCESS)
		literal_tokens = create_literal_tokens(input, shell);
	if ((*shell)->current_status == SUCCESS)
		interpreted_tokens = create_interpreted_tokens(literal_tokens,
				(*shell)->current_n_tokens, shell, LEXER);
	free_array(literal_tokens);
	if ((*shell)->current_status == SUCCESS)
		(*shell)->tokens = interpreted_tokens;
	else
		(*shell)->tokens = NULL;
	if (*input)
		free(*input);
}
