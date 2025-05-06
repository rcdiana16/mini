/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:06:40 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 18:09:20 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_builtin_or_exit_pipe(char **path_sp_w_slash, char **cmd_inf, \
	t_env *env_list, t_command *stru)
{
	char		*built_in_path;

	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf);
	if (!built_in_path)
	{
		exec_builtin_or_exit_pipe(cmd_inf, \
		stru, env_list, path_sp_w_slash);
	}
	return (built_in_path);
}

char	**allocate_cleaned_cmd(char **cmd_tokens)
{
	int		i;
	char	**cleaned_cmd;

	i = 0;
	while (cmd_tokens[i])
		i++;
	if (i == 0)
		return (NULL);
	cleaned_cmd = calloc(i + 1, sizeof(char *));
	cleaned_cmd[i] = NULL;
	return (cleaned_cmd);
}
