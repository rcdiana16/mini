/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:36:04 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 19:26:25 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*read_and_process_line(t_pipe_exec_info *pipe_exec_info)
{
	int		input_fd;
	char	*line;
	char	*tmp;

	write(STDOUT_FILENO, "> ", 2);
	input_fd = init_heredoc_io();
	if (input_fd < 0)
		return (NULL);
	line = get_next_line(input_fd);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (line)
	{
		tmp = line;
		line = replace_env_vars(line, pipe_exec_info->env_list, \
		pipe_exec_info->shell);
		free(tmp);
	}
	return (line);
}

static int	handle_single_heredoc_input(char *delimiter, int pipefd[2], \
		struct sigaction *sa_old, t_pipe_exec_info *pipe_exec_info)
{
	char	*line;

	line = read_and_process_line(pipe_exec_info);
	if (!line)
		return (1);
	if (check_heredoc_interrupt(line, pipefd, sa_old))
		return (1);
	if (process_heredoc_line(line, delimiter, pipefd))
		return (1);
	return (0);
}

int	handle_heredoc_loop(char *delimiter, int pipefd[2], \
		struct sigaction *sa_old, t_pipe_exec_info *pipe_exec_info)
{
	int	result;

	while (1)
	{
		result = handle_single_heredoc_input(delimiter, pipefd, sa_old, \
					pipe_exec_info);
		if (result != 0)
		{
			if (result == -1)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			return (result);
		}
	}
	return (0);
}

int	handle_heredoc_input(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;

	g_heredoc_interrupted = 0;
	if (pipe(pipefd) == -1)
		return (-1);
	init_here_doc_signals(&sa_new, &sa_old);
	if (handle_heredoc_loop(delimiter, pipefd, &sa_old, pipe_exec_info) == -1)
		return (-1);
	close(pipefd[1]);
	sigaction(SIGINT, &sa_old, NULL);
	return (pipefd[0]);
}
