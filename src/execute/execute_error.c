/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:47:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 16:07:15 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_empty_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(0);
}

void	handle_dotdot_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

void	handle_is_directory(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": Is a directory\n", 17);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(126);
}

void	handle_is_directory_empty(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	ft_putstr_fd(": No such file or directory\n", 2);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

void	handle_command_found(t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(126);
}
