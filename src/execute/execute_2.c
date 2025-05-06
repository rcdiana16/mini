/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:01:20 by diana             #+#    #+#             */
/*   Updated: 2025/04/23 14:08:15 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

char	*find_builtin_or_exit(char **path_sp_w_slash, t_command *cmd_inf, \
		t_env *env_list)
{
	char	*built_in_path;

	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf->tokens);
	if (!built_in_path)
		exec_builtin_or_exit(cmd_inf->tokens[0], \
		cmd_inf, env_list, path_sp_w_slash);
	return (built_in_path);
}
