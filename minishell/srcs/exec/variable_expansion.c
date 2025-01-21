/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/17 10:46:55 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	variable_expansion(t_shell **shell)
{
	if ((*(*((*shell)->current_command))->current_arg))
		(*((*shell)->current_command))->current_arg
			= &((*((*shell)->current_command))->args->next);
	cmd_name_var_expansion(shell);
	if ((*shell)->current_status != SUCCESS)
		return (ERROR);
	cmd_args_var_expansion(shell);
	if ((*shell)->current_status != SUCCESS)
		return (ERROR);
	cmd_io_files_var_expansion(shell, (*((*shell)->current_command))->in_files);
	if ((*shell)->current_status != SUCCESS)
		return (ERROR);
	cmd_io_files_var_expansion(shell,
		(*((*shell)->current_command))->out_files);
	if ((*shell)->current_status != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	bad_redirect(t_shell **shell, char **expand,
	char ***lit_tokens, char ***int_result)
{
	error_handler(shell, NULL, AMBIGUOUS_REDIRECT, ERR_AMBIGUOUS_REDIRECT);
	free_tmp_tokens(expand, lit_tokens, int_result);
	return (STOP);
}

int	free_tmp_tokens(char **expand, char ***literal_result,
		char ***interpreted_result)
{
	if (expand)
	{
		free(*expand);
		*expand = NULL;
	}
	if (literal_result)
	{
		free_array(*literal_result);
		*literal_result = NULL;
	}
	if (interpreted_result)
	{
		free(*interpreted_result);
		*interpreted_result = NULL;
	}
	return (STOP);
}
