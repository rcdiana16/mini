/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:30:45 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 10:14:13 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
}

void	init_here_doc_signals(struct sigaction *sa_new, \
	struct sigaction *sa_old)
{
	sa_new->sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa_new->sa_mask);
	sa_new->sa_flags = 0;
	sigaction(SIGINT, sa_new, sa_old);
}

int	check_heredoc_interrupt(char *line, int *pipefd, \
	struct sigaction *sa_old)
{
	if (g_heredoc_interrupted)
	{
		free(line);
		close(pipefd[0]);
		close(pipefd[1]);
		sigaction(SIGINT, sa_old, NULL);
		return (1);
	}
	return (0);
}
