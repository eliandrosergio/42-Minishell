/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/10 16:02:51 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(t_shell **shell)
{
	char	opt;
	t_list	*arg;

	arg = (*((*shell)->current_command))->args->next;
	opt = 0;
	if (arg)
		opt = built_in_echo_has_opt(arg->name);
	arg = arg;
	if (opt)
		arg = arg->next;
	while (arg)
	{
		ft_putstr_fd(arg->name, STDOUT_FILENO);
		arg = arg->next;
		if (arg)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!opt)
		write(STDOUT_FILENO, "\n", 1);
}

char	built_in_echo_has_opt(char *line)
{
	if (!line)
		return (false);
	if (!match_str(line, "-n", 0))
		return (false);
	line += 2;
	if (!*line)
		return (true);
	while (*line && *line == 'n')
		line++;
	if (*line)
		return (false);
	return (true);
}
