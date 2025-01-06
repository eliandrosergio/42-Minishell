/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:28:20 by antonfer          #+#    #+#             */
/*   Updated: 2024/11/27 08:28:57 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **args)
{
	int	status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	ft_cd(char **args)
{
	char	*home;

	if (args[1] == NULL)
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
		if (chdir(home) != 0)
			perror("mininshell: cd");
	}
	else if (chdir(args[1]) != 0)
		perror("minishell: cd");
}

void	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
		perror("minishell: pwd");
}

void	ft__exit(char **args)
{
	int		exit_code;
	char	*end;

	exit_code = 0;
	if (args[1] != NULL) // Verificar argumento
	{
		exit_code = strtol(args[1], &end, 10);
		if (*end != '\0')
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
			exit_code = 255;
		}
	}
	exit(exit_code);
}

void	ft_echo(char **args)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;

	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}