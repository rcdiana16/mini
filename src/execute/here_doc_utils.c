/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:21:20 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 07:57:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_heredoc_line(char *line, char *delimiter, int *pipefd)
{
	ssize_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, delimiter, len) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
	return (0);
}

int	init_heredoc_io(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (open("/dev/tty", O_RDONLY));
	return (STDIN_FILENO);
}
