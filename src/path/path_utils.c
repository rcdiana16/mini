/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:01:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 11:13:30 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_paths(char **path_splited)
{
	int	i;

	i = 0;
	while (path_splited[i])
		i++;
	return (i);
}

char	**allocate_paths_with_slash(char **path_splited, int count)
{
	char	**good_path;
	int		i;

	if (!path_splited)
		return (NULL);
	good_path = malloc(sizeof(char *) * (count + 1));
	if (!good_path)
		return (NULL);
	i = 0;
	while (i < count)
	{
		good_path[i] = ft_strjoin(path_splited[i], "/");
		if (!good_path[i])
		{
			while (--i >= 0)
				free(good_path[i]);
			free(good_path);
			return (NULL);
		}
		i++;
	}
	good_path[i] = NULL;
	return (good_path);
}

char	**add_slash(char **path_splited)
{
	int	count;

	if (!path_splited)
		return (NULL);
	count = count_paths(path_splited);
	return (allocate_paths_with_slash(path_splited, count));
}
