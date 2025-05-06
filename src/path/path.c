/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/27 14:47:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_path(char *path)
{
	char	**path_splited;

	if (!path)
		return (NULL);
	path_splited = ft_split(path, ':');
	if (!path_splited)
		return (NULL);
	return (path_splited);
}

char	**get_path(t_env *env_mini)
{
	char	*path;

	path = get_env_value(env_mini, "PATH");
	if (!path)
		path = "";
	return (split_path(path));
}

void	handle_path(char ***path_splitted, char ***path_sp_w_slash, \
	t_env *env_mini)
{
	if (*path_sp_w_slash)
		free_arr(*path_sp_w_slash);
	*path_splitted = get_path(env_mini);
	if (!*path_splitted)
	{
		write(2, "Error: get_path() returned NULL\n", \
			ft_strlen("Error: get_path() returned NULL\n"));
		exit(1);
	}
	*path_sp_w_slash = add_slash(*path_splitted);
	if (path_splitted)
		free_arr(*path_splitted);
	if (!*path_sp_w_slash)
	{
		write(2, "Error: add_slash() returned NULL\n", \
			ft_strlen("Error: add_slash() returned NULL\n"));
		exit(1);
	}
}
