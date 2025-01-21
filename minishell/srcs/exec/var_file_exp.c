/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_file_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 10:26:37 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_io_files_var_expansion(t_shell **shell, t_list *file)
{
	(*shell)->current_status = SUCCESS;
	while (file)
	{
		(*shell)->current_status = SUCCESS;
		if (file->token_type == LITERAL_TOKEN)
		{
			if (cmd_io_files_expand_tokens(shell, file) == STOP)
				return (STOP);
		}
		file = file->next;
	}
	return (SUCCESS);
}

int	cmd_io_files_expand_tokens(t_shell **shell, t_list *file)
{
	char	*expand;
	char	**lit_tokens;
	char	**int_tokens;

	expand = ft_join(file->name, NULL, str_len(file->name, NULL, 0));
	input_to_literal_input(shell, &expand, 0);
	lit_tokens = create_literal_tokens(&expand, shell);
	if (lit_tokens && (!lit_tokens[0] || lit_tokens[1]))
		return (bad_redirect(shell, &expand, &lit_tokens, NULL));
	if (cmd_args_get_int_tokens(shell, &lit_tokens, &int_tokens) == STOP)
		return (free_tmp_tokens(&expand, &lit_tokens, &int_tokens));
	if (!int_tokens[0] || int_tokens[1])
		return (bad_redirect(shell, &expand, &lit_tokens, &int_tokens));
	file->name = int_tokens[0];
	file->token_type = EXPANDED_TOKEN;
	free_tmp_tokens(&expand, &lit_tokens, &int_tokens);
	return (SUCCESS);
}
