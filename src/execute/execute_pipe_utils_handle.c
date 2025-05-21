/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:18:11 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 19:16:33 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_input_redirection(t_pipe_exec_info *pipe_exec_info)
{
	if (pipe_exec_info->cmd_info->file_in)
	{
		if (pipe_exec_info->cmd_info->fd_in != -1)
		{
			dup2(pipe_exec_info->cmd_info->fd_in, STDIN_FILENO);
			close(pipe_exec_info->cmd_info->fd_in);
		}
		else
		{
			free_arr(pipe_exec_info->current_command);
			free_all(pipe_exec_info->cmd_info, pipe_exec_info->path_sp_w_slash, \
			pipe_exec_info->env_list);
			close(0);
			close(1);
			get_next_line(-42);
			return (1);
		}
	}
	return (0);
}

static int	handle_output_redirection(t_pipe_exec_info *pipe_exec_info)
{
	if (pipe_exec_info->cmd_info->file_out)
	{
		if (pipe_exec_info->cmd_info->fd_out != -1)
		{
			dup2(pipe_exec_info->cmd_info->fd_out, STDOUT_FILENO);
			close(pipe_exec_info->cmd_info->fd_out);
		}
		else
		{
			free_arr(pipe_exec_info->current_command);
			free_all(pipe_exec_info->cmd_info, pipe_exec_info->path_sp_w_slash, \
			pipe_exec_info->env_list);
			close(0);
			close(1);
			get_next_line(-42);
			return (1);
		}
	}
	return (0);
}

static int	handle_redirection_bis(t_pipe_exec_info *pipe_exec_info)
{
	if (handle_input_redirection(pipe_exec_info))
		return (1);
	if (handle_output_redirection(pipe_exec_info))
		return (1);
	return (0);
}

static int	handle_builtin(t_pipe_exec_info *pipe_exec_info)
{
	int	exit_builtin;

	exit_builtin = check_builtins(pipe_exec_info->current_command, \
			pipe_exec_info->env_list, pipe_exec_info->cmd_info, \
			pipe_exec_info->path_sp_w_slash);
	if (exit_builtin != -1)
	{
		restore_heredoc_stdin(pipe_exec_info->cmd_info);
		close(0);
		close(1);
		free_all(pipe_exec_info->cmd_info, pipe_exec_info->path_sp_w_slash, \
				pipe_exec_info->env_list);
		free_arr(pipe_exec_info->current_command);
		get_next_line(-42);
		return (exit_builtin);
	}
	return (-1);
}

int	handle_redirection_and_builtins(t_pipe_exec_info *pipe_exec_info)
{
	int	status;

	status = handle_redirection_bis(pipe_exec_info);
	if (status != 0)
		return (status);
	return (handle_builtin(pipe_exec_info));
}
