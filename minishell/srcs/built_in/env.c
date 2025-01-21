/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_env(t_shell **shell)
{
	int		env;
	t_list	*arg;

	env = 0;
	arg = (*((*shell)->current_command))->args->next;
	if (arg && *(arg->name) == '-')
	{
		error_handler(shell, arg->name, ERROR, ERR_NO_OPT);
		return ;
	}
	else if (arg)
	{
		error_handler(shell, arg->name, ERROR, ERR_NO_ARG);
		return ;
	}
	while ((*shell)->envp_cpy[env])
	{
		if (ft_strchr((*shell)->envp_cpy[env], '='))
		{
			ft_putstr_fd((*shell)->envp_cpy[env], STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		env++;
	}
}
