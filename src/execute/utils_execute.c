/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:18:44 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/28 11:50:55 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_child_processes(int *pids, int pipe_count)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i <= pipe_count)
	{
		waitpid(pids[i], &exit_status, 0);
		i++;
	}
	set_signals();
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (0);
}
