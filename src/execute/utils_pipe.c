/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:52:12 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/21 19:27:12 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_pipe_bounds(t_command *cmd_info, int i, int *start, int *end)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	*start = 0;
	while (cmd_info->tokens[j])
	{
		if (ft_strncmp(cmd_info->tokens[j], "|", 1) == 0)
		{
			count++;
			if (count == i)
				*start = j + 1;
		}
		j++;
	}
	if (count < i)
		return (0);
	*end = *start;
	while (cmd_info->tokens[*end] && \
		ft_strncmp(cmd_info->tokens[*end], "|", 1) != 0)
		(*end)++;
	return (1);
}

char	**get_pipe_command(t_command *cmd_info, int i)
{
	int		start;
	int		end;
	int		j;
	char	**pipe_command;

	if (!get_pipe_bounds(cmd_info, i, &start, &end))
		return (NULL);
	pipe_command = malloc(sizeof(char *) * (end - start + 1));
	if (!pipe_command)
		return (NULL);
	j = 0;
	while (start < end)
	{
		pipe_command[j] = ft_strdup(cmd_info->tokens[start]);
		start++;
		j++;
	}
	pipe_command[j] = NULL;
	return (pipe_command);
}

int	create_pipe(int *pipe_fd)
{
	return (pipe(pipe_fd));
}

void	child_process_setup_io(t_pipe_exec_info *pipe_exec_info)
{
	if (pipe_exec_info->cmd_info->file_in)
	{
		dup2(pipe_exec_info->cmd_info->fd_in, STDIN_FILENO);
		close(pipe_exec_info->cmd_info->fd_in);
	}
	else if (pipe_exec_info->prev_pipe_fd != -1)
	{
		dup2(pipe_exec_info->prev_pipe_fd, STDIN_FILENO);
		close(pipe_exec_info->prev_pipe_fd);
	}
	if (pipe_exec_info->cmd_info->file_out)
	{
		dup2(pipe_exec_info->cmd_info->fd_out, STDOUT_FILENO);
		close(pipe_exec_info->cmd_info->fd_out);
	}
	else if (pipe_exec_info->i < pipe_exec_info->cmd_info->c_pipe)
	{
		dup2(pipe_exec_info->pipe_fd[1], STDOUT_FILENO);
		if (pipe_exec_info->pipe_fd[0] != -1)
			close(pipe_exec_info->pipe_fd[0]);
		if (pipe_exec_info->pipe_fd[1] != -1)
			close(pipe_exec_info->pipe_fd[1]);
	}
}

int	execute_child_process_pipe_helper(t_pipe_exec_info *pipe_exec_info)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_process_setup_io(pipe_exec_info);
	return (child_process_execute_command(pipe_exec_info));
}
