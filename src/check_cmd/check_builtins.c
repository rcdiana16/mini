/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/05/20 17:28:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_echo(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0]) + 1) == 0)
	{
		ft_our_echo(cmd);
		return (0);
	}
	return (-1);
}

static int	check_cd(char **cmd, t_env *env, t_command *info)
{
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0]) + 1) == 0)
		return (is_valid_path(cmd[1], env, info, &cmd[0]));
	return (-1);
}

static int	check_pwd_env_exit(char **cmd, t_env *env, \
		t_command *info, char **path)
{
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]) + 1) == 0)
	{
		ft_our_pwd(env);
		return (0);
	}
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0]) + 1) == 0)
		return (ft_our_env(env, &cmd[0]));
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0]) + 1) == 0)
		return (ft_our_exit(env, info->tokens, info, path));
	return (-1);
}

int	check_standard_builtins(char **command, t_env *env_mini, \
		t_command **cmd_info, char **path)
{
	int	i;
	int	res;

	i = 0;
	if (!command)
		return (0);
	while (command[i])
	{
		if (ft_strncmp(command[i], "", 2) == 0)
		{
			i++;
			continue ;
		}
		res = check_echo(&command[i]);
		if (res != -1)
			return (res);
		res = check_cd(&command[i], env_mini, *cmd_info);
		if (res != -1)
			return (res);
		res = check_pwd_env_exit(&command[i], env_mini, *cmd_info, path);
		if (res != -1)
			return (res);
		return (-1);
	}
	return (0);
}

int	check_env_builtins(char **command, t_env *env_mini)
{
	int	exit;

	exit = 0;
	if (!command || !command[0])
		return (0);
	if ((ft_strncmp(command[0], "export", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] == NULL)
		{
			if (env_mini)
				return (print_sorted_env(env_mini));
		}
		else
		{
			exit = ft_export(env_mini, command);
			return (exit);
		}
	}
	else if ((ft_strncmp(command[0], "unset", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] != NULL && env_mini)
			ft_unset(env_mini, command);
		return (0);
	}
	return (-1);
}
