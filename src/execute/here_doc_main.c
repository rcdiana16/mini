/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:36:04 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 07:56:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc_loop(char *delimiter, \
	int pipefd[2], struct sigaction *sa_old)
{
	char	*line;
	int		input_fd;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		input_fd = init_heredoc_io();
		if (input_fd < 0)
		{
			perror("minishell: heredoc input error");
			close(pipefd[0]);
			close(pipefd[1]);
			return (-1);
		}
		line = get_next_line(input_fd);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (!line || check_heredoc_interrupt(line, pipefd, sa_old))
			break ;
		if (process_heredoc_line(line, delimiter, pipefd))
			break ;
	}
	return (0);
}

int	handle_heredoc_input(char *delimiter)
{
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;

	g_heredoc_interrupted = 0;
	if (pipe(pipefd) == -1)
		return (-1);
	init_here_doc_signals(&sa_new, &sa_old);
	if (handle_heredoc_loop(delimiter, pipefd, &sa_old) == -1)
		return (-1);
	close(pipefd[1]);
	sigaction(SIGINT, &sa_old, NULL);
	return (pipefd[0]);
}
