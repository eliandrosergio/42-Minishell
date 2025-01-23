/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/23 12:03:46 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_oldpwd_and_pwd_path(t_shell *shell)
{
	t_env	*oldpwd;
	t_env	*pwd;
	t_env	*tmp;

	tmp = shell->envp_list;
	pwd = NULL;
	oldpwd = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
			oldpwd = tmp;
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
			pwd = tmp;
		tmp = tmp->next;
	}
	if (oldpwd != NULL && oldpwd->value != NULL)
		free(oldpwd->value);
	if (oldpwd != NULL && pwd != NULL)
		oldpwd->value = ft_strdup(pwd->value);
	else if (pwd == NULL && oldpwd != NULL)
		oldpwd->value = NULL;
	if (pwd != NULL && pwd->value != NULL)
		free(pwd->value);
	if (pwd != NULL)
		pwd->value = getcwd(NULL, 0);
}

int	ft_validate_cd_args(t_cmd *cmd)
{
	if (cmd->argc == 1)
	{
		ft_putstr_fd("minishell: cd: no directory specified\n", 2);
		return (0);
	}
	else if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (2);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	int			chdir_ret;
	struct stat	buf;
	int			arg_check;

	arg_check = ft_validate_cd_args(cmd);
	if (arg_check != 2)
		return (arg_check);
	chdir_ret = chdir(cmd->args[1]);
	if (chdir_ret == -1)
	{
		buf.st_mode = 0;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		if (!S_ISDIR(buf.st_mode))
			ft_putstr_fd(": is not a directory\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	ft_update_oldpwd_and_pwd_path(shell);
	return (0);
}
