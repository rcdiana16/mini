/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:59:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 18:25:11 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_child_process_pipe(char **cmd_info, char **path_sp_w_slash, \
	t_env *env_list, t_command *stru)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info[0])
		return (0);
	stru->envp = convert_env_to_array(env_list);
	if (cmd_info[0][0] == '/' || \
	ft_strchr(cmd_info[0], '/') != NULL)
	{
		execve(cmd_info[0], cmd_info, stru->envp);
		exec_builtin_or_exit_pipe(cmd_info, \
		stru, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit_pipe(path_sp_w_slash, \
		cmd_info, env_list, stru);
	execve(built_in_path, cmd_info, stru->envp);
	free(built_in_path);
	exec_builtin_or_exit_pipe(cmd_info, stru, env_list, \
	path_sp_w_slash);
	return (0);
}

static int	handle_redirection_tokens(char **cmd_tokens, \
	t_command *cmd_info, int *i, t_pipe_exec_info *pipe_exec_info)
{
	int	ret;

	while (cmd_tokens[*i] && (ft_strncmp(cmd_tokens[*i], ">", 1) == 0 || \
		ft_strncmp(cmd_tokens[*i], ">>", 2) == 0 || \
		ft_strncmp(cmd_tokens[*i], "<", 1) == 0 || \
		ft_strncmp(cmd_tokens[*i], "<<", 2) == 0) && \
		cmd_tokens[*i + 1])
	{
		ret = handle_redirection(cmd_tokens, cmd_info, i, pipe_exec_info);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

static void	copy_normal_token_pipe(char **cmd_tokens, \
char **cleaned_cmd, int *j, int i)
{
	if (cmd_tokens[i])
		cleaned_cmd[*j] = ft_strdup(cmd_tokens[i]);
	(*j)++;
}

int	filter_and_copy_tokens(char **cmd_tokens, t_command *cmd_info, \
	char **cleaned_cmd, t_pipe_exec_info *pipe_exec_info)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	if (!cmd_tokens)
		return (0);
	while (cmd_tokens[i])
	{
		ret = \
		handle_redirection_tokens(cmd_tokens, cmd_info, &i, pipe_exec_info);
		if (ret == -1)
			return (-1);
		if (cmd_tokens[i])
		{
			copy_normal_token_pipe(cmd_tokens, cleaned_cmd, &j, i);
			i++;
		}
	}
	cleaned_cmd[j] = NULL;
	return (0);
}

char	**clean_redir(char **cmd_tokens, t_command *cmd_info, \
						t_pipe_exec_info *pipe_exec_info)
{
	char	**cleaned_cmd;

	cleaned_cmd = allocate_cleaned_cmd(cmd_tokens);
	if (!cleaned_cmd)
		return (NULL);
	filter_and_copy_tokens(cmd_tokens, cmd_info, cleaned_cmd, pipe_exec_info);
	if (cmd_tokens != cleaned_cmd)
		free_arr(cmd_tokens);
	return (cleaned_cmd);
}
