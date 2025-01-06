/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupesa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:24:11 by akupesa           #+#    #+#             */
/*   Updated: 2024/12/21 15:24:26 by akupesa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

void	ft_export(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "minishell: export: expected argument\n");
		return;
	}
	if (putenv(args[1]) != 0) // Formato esperado: VAR=value
	{
		perror("minishell: export");
	}
}
