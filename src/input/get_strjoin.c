/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:27:27 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 01:27:42 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_strjoin_arr(char *first, char **arr)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	while (arr && arr[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[0] = ft_strdup(first);
	i = 0;
	while (i < len)
	{
		new_arr[i + 1] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[len + 1] = NULL;
	free_arr(arr);
	return (new_arr);
}
