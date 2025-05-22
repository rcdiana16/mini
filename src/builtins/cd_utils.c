/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:02:56 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/22 16:49:56 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_flag_1(t_env *env, char *new_path)
{
	if (!env || !new_path)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(new_path);
	if (!env->value)
		return ;
}

void	handle_flag_3(t_env *env, char *new_path)
{
	if (!env || !new_path)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(new_path);
}

void	update_env(t_env *env, char *new_path, char *env_to_update, int flag)
{
	char	*current_pwd;

	if (!new_path | ! env_to_update)
		return ;
	current_pwd = get_env_value(env, env_to_update);
	if (!current_pwd && ft_strncmp(env_to_update, "OLDPWD", 7) == 0)
	{
		append_node(&env, env_to_update, new_path);
		return ;
	}
	if (!current_pwd)
		return ;
	while (env)
	{
		if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0)
		{
			if (flag == 1)
				handle_flag_1(env, new_path);
			else if (flag == 3)
				handle_flag_3(env, new_path);
			return ;
		}
		env = env->next;
	}
}

int	print_cd_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory\n", 18);
		close(fd);
	}
	else
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
	}
	return (1);
}

void	update_pwd_env(t_env *env_mini, char *oldpwd, char *path)
{
	char	*cwd;

	cwd = calloc(256, 4);
	if (!oldpwd | !path | !cwd)
	{
		free(cwd);
		return ;
	}
	if (path[0] == '/')
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, getcwd(cwd, 1024), "PWD", 1);
	}
	else
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, getcwd(cwd, 1024), "PWD", 1);
	}
	free(cwd);
}
