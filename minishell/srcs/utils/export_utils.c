/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 11:40:55 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	built_in_export_escape_char(char *envp)
{
	int	len;

	len = 0;
	while (envp[len])
	{
		if (envp[len] == '"' || envp[len] == '\\' || envp[len] == '$')
		{
			if (len)
				write(STDOUT_FILENO, envp, len);
			write(STDOUT_FILENO, "\\", 1);
			write(STDOUT_FILENO, envp + len, 1);
			return (len + 1);
		}
		len++;
	}
	write(STDOUT_FILENO, envp, len);
	return (len);
}

void	built_in_export_display_env(char *envp)
{
	int	i;

	if (!is_valid_identifier(envp))
	{
		write(STDERR_FILENO, "minishell: export: '", 20);
		write(STDERR_FILENO, envp, strlen(envp));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		return ;
	}
	i = 0;
	while (envp[i])
		i += built_in_export_escape_char(envp + i);
}
