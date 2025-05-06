/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:30 by diana             #+#    #+#             */
/*   Updated: 2025/03/27 15:12:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_to_exc(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

char	**build_command_paths(char **good_path, char *command)
{
	int		i;
	char	**tmp_path;

	if (!good_path || !command)
		return (NULL);
	i = count_paths(good_path);
	tmp_path = malloc(sizeof(char *) * (i + 1));
	if (!tmp_path)
		return (NULL);
	i = 0;
	while (good_path[i])
	{
		tmp_path[i] = ft_strjoin(good_path[i], command);
		if (!tmp_path[i])
		{
			while (--i >= 0)
				free(tmp_path[i]);
			free(tmp_path);
			return (NULL);
		}
		i++;
	}
	tmp_path[i] = NULL;
	return (tmp_path);
}

void	free_path_array(char **path_array, char *exclude)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		if (path_array[i] != exclude)
			free(path_array[i]);
		i++;
	}
	free(path_array);
}

char	*check_current_dir_command(char **command)
{
	char	*current_dir_command;

	current_dir_command = malloc(ft_strlen(command[0]) + 3);
	if (!current_dir_command)
		return (NULL);
	ft_strlcpy(current_dir_command, "./", 3);
	ft_strlcat(current_dir_command, command[0], ft_strlen(command[0]) + 3);
	if (access(current_dir_command, X_OK) == 0)
		return (current_dir_command);
	free(current_dir_command);
	return (NULL);
}

char	*find_no_builtin(char **good_path, char **command)
{
	char	**tmp_path;
	char	*result;

	if (!command)
		return (NULL);
	if (!good_path || !*good_path)
		return (check_current_dir_command(command));
	tmp_path = build_command_paths(good_path, command[0]);
	if (!tmp_path)
		return (NULL);
	result = path_to_exc(tmp_path);
	free_path_array(tmp_path, result);
	return (result);
}
