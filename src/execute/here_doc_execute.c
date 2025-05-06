/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:39:32 by diana             #+#    #+#             */
/*   Updated: 2025/05/06 19:43:31 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_heredoc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	int	heredoc_fd;
	int	saved_stdin;

	heredoc_fd = handle_heredoc_input(delimiter);
	if (heredoc_fd == -1)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		close(heredoc_fd);
		return (-1);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		close(heredoc_fd);
		close(saved_stdin);
		return (-1);
	}
	pipe_exec_info->cmd_info->fd_here_doc = saved_stdin;
	pipe_exec_info->cmd_info->here_doc = 1;
	pipe_exec_info->cmd_info->fd_in = heredoc_fd;
	return (0);
}

void	restore_heredoc_stdin(t_command *cmd_info)
{
	if (cmd_info->here_doc /*&& cmd_info->c_pipe == 0*/)
	{
		if (dup2(cmd_info->fd_here_doc, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
		}
		close(cmd_info->fd_here_doc);
		cmd_info->fd_here_doc = -1;
		close(cmd_info->fd_in);
		cmd_info->fd_in = -1;
		cmd_info->here_doc = 0;
	}
}

void	handle_heredoc_redirection(char **cmd_tokens, int *i, \
		t_pipe_exec_info *pipe_exec_info)
{
	if (cmd_tokens[*i + 1])
	{
		if (execute_heredoc(cmd_tokens[*i + 1], pipe_exec_info) == -1)
		{
			*i += 2;
			return ;
		}
		*i += 2;
	}
}
