/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:31:22 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 17:32:00 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_cmd_values(char **cmd, char **value)
{
	char	*temp;

	if (!cmd || !cmd[1])
		return ;
	if (cmd[0][0] == '\"' || cmd[0][0] == '\'')
	{
		temp = ft_strjoin(*value, " ");
		*value = ft_strjoin(temp, cmd[1]);
		free(temp);
	}
	else
		*value = ft_strdup(cmd[1]);
}
