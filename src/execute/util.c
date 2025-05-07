/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 11:33:51 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_empty_command_pip(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list, char **command)
{
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	free_arr(command);
	exit(0);
}

void	handle_dotdot_command_pip(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list, char **command)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	free_arr(command);
	exit(127);
}

void	handle_is_directory_pip(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash, char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": Is a directory\n", 17);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	free_arr(command);
	exit(126);
}

void	handle_command_not_found_pip(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash, char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 20);
	close_fd(cmd_info);
	free_arr(command);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

void	exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	struct stat	info;

	get_next_line(-42);
	if (ft_strncmp(command[0], "", 2) == 0)
		handle_empty_command_pip(cmd_info, path_sp_w_slash, env_list, command);
	if (ft_strncmp(command[0], "..", 3) == 0)
		handle_dotdot_command_pip(cmd_info, path_sp_w_slash, env_list, command);
	if (stat(command[0], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			handle_is_directory_pip(cmd_info, env_list, \
				path_sp_w_slash, command);
	}
	handle_command_not_found_pip(cmd_info, env_list, path_sp_w_slash, command);
}
