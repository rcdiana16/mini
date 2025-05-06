/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:14 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 15:51:11 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_stdout(t_command *cmd_info)
{
	if ((cmd_info->c_red_o != 0 || cmd_info->c_append != 0) && \
	cmd_info->file_out && cmd_info->fd_out != -1)
	{
		if (cmd_info->og_stdout != -1)
		{
			if (dup2(cmd_info->og_stdout, STDOUT_FILENO) == -1)
			{
				perror("dup2 stdout");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (cmd_info->og_stdout != -1)
	{
		close(cmd_info->og_stdout);
		cmd_info->og_stdout = -1;
	}
}

void	reset_stdin(t_command *cmd_info)
{
	if ((cmd_info->c_red_i != 0 || cmd_info->here_doc != 0) && \
	cmd_info->file_in && cmd_info->fd_in != -1)
	{
		if (cmd_info->og_stdin != -1)
		{
			if (dup2(cmd_info->og_stdin, STDIN_FILENO) == -1)
			{
				perror("dup2 stdin");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (cmd_info->og_stdin != -1)
	{
		close(cmd_info->og_stdin);
		cmd_info->og_stdin = -1;
	}
}

void	handle_cmd_info(t_command *cmd_info)
{
	if (cmd_info)
	{
		reset_stdout(cmd_info);
		reset_stdin(cmd_info);
		close_fd(cmd_info);
		free_command(cmd_info);
	}
}
