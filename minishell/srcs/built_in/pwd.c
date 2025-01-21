/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(t_shell **shell)
{
	t_list	*arg;
	size_t	len;

	arg = NULL;
	if ((*((*shell)->current_command))->args)
		arg = (*((*shell)->current_command))->args->next;
	if (arg && *(arg->name) == '-')
	{
		error_handler(shell, arg->name, ERROR, ERR_NO_OPT);
		return ;
	}
	len = str_len((*shell)->saved_pwd, NULL, 0);
	if (len > 1 && (*shell)->saved_pwd[len - 1] == '/')
		len--;
	write(STDOUT_FILENO, (*shell)->saved_pwd, len);
	write(STDOUT_FILENO, "\n", 1);
}
