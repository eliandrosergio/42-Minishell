/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:42:30 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_env(char **envp)
{
	int	n;

	n = 0;
	while (envp[n])
		n++;
	return (n);
}

int	match_env(char *current, char *s2)
{
	if (!current || !s2)
		return (false);
	while (*current && *s2 && *current == *s2)
	{
		if (*current == '=')
			return (true);
		current++;
		s2++;
	}
	if ((!*current || *current == '=') && (!*s2 || *s2 == '='))
		return (true);
	return (false);
}

int	change_env(t_shell **shell, char **envp, char *name, int internal)
{
	int	len;

	if (!ft_strchr(name, '='))
		return (SUCCESS);
	len = str_len(name, NULL, 0);
	free(*envp);
	*envp = ft_join(name, NULL, len);
	if (!(*envp))
	{
		if (internal)
			return (ERROR);
		error_handler(shell, NULL, INTERNAL_ERROR, ERR_INTERNAL);
	}
	return (SUCCESS);
}
