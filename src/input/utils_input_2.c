/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:36:16 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 07:38:11 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*initialize_command(t_shell *shell)
{
	t_command	*cmd_info;

	cmd_info = NULL;
	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->envp = NULL;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->here_doc = 0;
	cmd_info->c_red_o = 0;
	cmd_info->quotes_s = 0;
	cmd_info->quotes_d = 0;
	cmd_info->exit_code = shell->exit_code;
	cmd_info->file_out = NULL;
	cmd_info->file_in = NULL;
	cmd_info->fd_here_doc = 0;
	cmd_info->c_append = 0;
	cmd_info->flag_test = 0;
	cmd_info->og_stdout = dup(STDOUT_FILENO);
	cmd_info->og_stdin = dup(STDIN_FILENO);
	return (cmd_info);
}

void	handle_single_quotes(t_command *cmd_info, int i)
{
	if (cmd_info->tokens[i])
		make_good_cmd(cmd_info->tokens[i]);
}

void	process_tokens(t_command *cmd_info, t_env *env_mini, t_shell *shell)
{
	int	i;

	if (!cmd_info->tokens || !cmd_info->tokens[0])
		return ;
	i = 0;
	while (cmd_info->tokens[i])
	{
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			remove_single_quotes(cmd_info->tokens[i]);
		else
		{
			if (!has_enclosed_double_quotes(cmd_info->tokens[i]))
				remove_single_quotes(cmd_info->tokens[i]);
			handle_double_quotes_and_env_vars(cmd_info, env_mini, shell, i);
		}
		i++;
	}
}
