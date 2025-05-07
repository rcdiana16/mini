/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:32 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 10:38:50 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info->tokens[0])
		return (0);
	cmd_info->envp = convert_env_to_array(env_list);
	if (cmd_info->tokens[0][0] == '/' || \
	ft_strchr(cmd_info->tokens[0], '/') != NULL)
	{
		execve(cmd_info->tokens[0], cmd_info->tokens, \
		cmd_info->envp);
		exec_builtin_or_exit(cmd_info->tokens[0], \
		cmd_info, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit(path_sp_w_slash, cmd_info, \
	env_list);
	execve(built_in_path, cmd_info->tokens, cmd_info->envp);
	free(built_in_path);
	exec_builtin_or_exit(cmd_info->tokens[0], cmd_info, env_list, \
	path_sp_w_slash);
	return (0);
}

int	prepare_execution(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list, t_pipe_exec_info *pipe_exec_info)
{
	int	exit_builtin;

	if (cmd_info->c_pipe >= 1)
		return (execute_pipes(cmd_info, path_sp_w_slash, env_list));
	cmd_info->tokens = clean_redir(cmd_info->tokens, cmd_info, pipe_exec_info);
	if (!manage_redirection(cmd_info))
		return (1);
	if (cmd_info->flag_test == 1)
		return (1);
	exit_builtin = execute_builtin(cmd_info, env_list, path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	return (-1);
}

static void	init_pipe_exec_info(t_pipe_exec_info *info, \
	t_command *cmd_info, char **path_sp_w_slash, t_env *env_list)
{
	info->prev_pipe_fd = -1;
	info->path_sp_w_slash = path_sp_w_slash;
	info->env_list = env_list;
	info->cmd_info = cmd_info;
	info->shell = NULL;
}

static int	handle_parent_process(int pid, t_command *cmd_info)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signals();
	restore_heredoc_stdin(cmd_info);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	return (0);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int					pid;
	int					status;
	t_pipe_exec_info	info;

	init_pipe_exec_info(&info, cmd_info, path_sp_w_slash, env_list);
	status = prepare_execution(cmd_info, path_sp_w_slash, env_list, &info);
	if (status != -1)
		return (status);
	pid = fork();
	if (pid == 0)
		execute_in_child(cmd_info, path_sp_w_slash, env_list);
	return (handle_parent_process(pid, cmd_info));
}
