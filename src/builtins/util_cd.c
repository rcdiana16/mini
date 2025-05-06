/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:06:29 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 11:10:06 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
char	*ft_find_dir(char *path)
{
	int	i;
	int	c_slash;

	c_slash = 0;
	if (!path)
		return (NULL);
	i = ft_strlen(path) - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	return (path + c_slash);
}

char	*ft_find_gd_dir(char *path)
{
	int		i;
	int		c_slash;
	char	*good_path;

	if (!path)
		return (NULL);
	i = ft_strlen(path) - 1;
	c_slash = 0;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	good_path = ft_strndup(path, c_slash);
	if (!good_path)
		return (NULL);
	return (good_path);
}
*/

/*
void	handle_flag_0(t_env *env, char *new_path)
{
	char	*last_dir;

	if (!new_path)
		return ;
	last_dir = ft_strdup(ft_find_dir(new_path));
	if (!last_dir)
		return ;
	env->value = ft_strjoin(env->value, last_dir);
	free(last_dir);
}
*/

/*void	handle_flag_4(t_env *env, char *new_path)
{
	if (!new_path)
		return ;
	env->value = ft_strdup(ft_find_gd_dir(new_path));
}*/
/*
void	update_env_concat(t_env *env, char *current_pwd, char *new_path)
{
	char	*temp;

	if (!current_pwd | !new_path)
		return ;
	temp = ft_strjoin(current_pwd, "/");
	if (!temp)
		return ;
	free(env->value);
	env->value = ft_strjoin(temp, new_path);
	free(temp);
}

void	update_env_last_dir(t_env *env, char *new_path)
{
	char	*last_dir;

	if (!new_path)
		return ;
	last_dir = ft_strdup(ft_find_dir(new_path));
	if (!last_dir)
		return ;
	free(env->value);
	env->value = ft_strjoin(env->value, last_dir);
	free(last_dir);
}

void	update_env_direct(t_env *env, char *new_path, int flag)
{
	if (!new_path)
		return ;
	free(env->value);
	if (flag == 3)
		env->value = ft_strdup(new_path);
	else if (flag == 4)
		env->value = ft_strdup(ft_find_gd_dir(new_path));
}*/