/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_auxiliar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:28:19 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 02:28:32 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	child_process_execute_command(t_pipe_exec_info *pipe_exec_info)
{
	char	**tmp_command;
	int		exit_builtin;

	tmp_command = clean_redir(pipe_exec_info->current_command, \
			pipe_exec_info->cmd_info, pipe_exec_info);
	if (!tmp_command)
		return (1);
	pipe_exec_info->current_command = tmp_command;
	exit_builtin = handle_redirection_and_builtins(pipe_exec_info);
	if (exit_builtin != -1)
		return (exit_builtin);
	execute_child_process_pipe(pipe_exec_info->current_command, \
									pipe_exec_info->path_sp_w_slash, \
									pipe_exec_info->env_list, \
									pipe_exec_info->cmd_info);
	return (127);
}
