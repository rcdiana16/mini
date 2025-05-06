/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_nothing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:22:04 by diana             #+#    #+#             */
/*   Updated: 2025/03/19 12:50:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handle_sigquit;
	action.sa_flags = 0;
	sigaction(SIGQUIT, &action, NULL);
}
