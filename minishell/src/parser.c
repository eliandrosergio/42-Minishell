/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:29:26 by antonfer          #+#    #+#             */
/*   Updated: 2024/11/27 08:30:39 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_and_execute(char *line)
{
    char *args[1000];
    int i = 0;
    char *token;

    token = strtok(line, " \n");
    while (token)
    {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    // Verificar comandos built-in
    if (args[0] == NULL)
        return; // Comando vazio

    if (strcmp(args[0], "cd") == 0)
    {
        handle_cd(args);
    }
	if (strcmp(args[0], "echo") == 0)
	{
		handle_echo(args);
	}
	if (strcmp(args[0], "export") == 0)
	{
    	handle_export(args);
	}
	if (strcmp(args[0], "env") == 0)
	{
		handle_env();
	}
    else if (strcmp(args[0], "pwd") == 0)
    {
        handle_pwd();
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        handle_exit(args);
    }
    else
    {
        execute_command(args); // Outros comandos
    }
}