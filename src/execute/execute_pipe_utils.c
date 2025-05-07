/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:32:31 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 15:51:10 by maximemarti      ###   ########.fr       */
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

int	execute_pipes_child_process(t_pipe_exec_info *pipe_exec_info, \
	int *pids, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_child_process_pipe_helper(pipe_exec_info);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pids[i] = pid;
		if (pipe_exec_info->prev_pipe_fd != -1)
			close(pipe_exec_info->prev_pipe_fd);
		if (i < pipe_exec_info->cmd_info->c_pipe)
			pipe_exec_info->prev_pipe_fd = pipe_exec_info->pipe_fd[0];
		if (pipe_exec_info->pipe_fd[1] != -1)
			close(pipe_exec_info->pipe_fd[1]);
		pipe_exec_info->pipe_fd[1] = -1;
		free_arr(pipe_exec_info->current_command);
		return (0);
	}
}

int	execute_pipes_loop(t_pipe_exec_info *pipe_exec_info, \
	int *pids, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->c_pipe)
	{
		close_fd(cmd_info);
		pipe_exec_info->current_command = get_pipe_command(cmd_info, i);
		if (!pipe_exec_info->current_command)
		{
			free(pids);
			return (1);
		}
		if (i < cmd_info->c_pipe)
			create_pipe(pipe_exec_info->pipe_fd);
		pipe_exec_info->i = i;
		if (execute_pipes_child_process(pipe_exec_info, pids, i) != 0)
		{
			free(pids);
			free_arr(pipe_exec_info->current_command);
			return (1);
		}
		i++;
	}
	pipe_exec_info->current_command = NULL;
	return (0);
}

int	execute_pipes(t_command *cmd_info, char **path_sp_w_slash, t_env *env_list)
{
	t_pipe_exec_info	pipe_exec_info;
	int					pids[250];
	int					return_value;

	pipe_exec_info.prev_pipe_fd = -1;
	pipe_exec_info.path_sp_w_slash = path_sp_w_slash;
	pipe_exec_info.env_list = env_list;
	pipe_exec_info.cmd_info = cmd_info;
	if (cmd_info->c_pipe > 100)
		return (0);
	if (execute_pipes_loop(&pipe_exec_info, pids, cmd_info) != 0)
		return (1);
	return_value = wait_for_child_processes(pids, cmd_info->c_pipe);
	return (return_value);
}
