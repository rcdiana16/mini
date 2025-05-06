/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:06:53 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/13 15:36:16 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_arr(char **tok)
{
	int	i;

	i = 0;
	if (!tok)
		return ;
	while (tok[i])
	{
		free(tok[i]);
		i++;
	}
	free(tok);
}

void	free_all(t_command *cmd_info, char **path_sp_w_slash, \
		t_env *env_list)
{
	free_arr(path_sp_w_slash);
	free_env_list(env_list);
	free_command(cmd_info);
}
