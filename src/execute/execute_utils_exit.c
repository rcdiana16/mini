/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:00:11 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 15:57:03 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	struct stat	info;
	char		*path_val;

	get_next_line(-42);
	if (ft_strncmp(command, "", 2) == 0)
		handle_empty_command(cmd_info, path_sp_w_slash, env_list);
	else if (ft_strncmp(command, "..", 3) == 0)
		handle_dotdot_command(cmd_info, path_sp_w_slash, env_list);
	else if (ft_strncmp(command, "./", 2) == 0 && stat(command, &info) != 0)
		handle_is_directory_empty(command, cmd_info, env_list, path_sp_w_slash);
	else if (stat(command, &info) == 0 && ft_strncmp(command, ".", 2) != 0)
	{
		if (S_ISDIR(info.st_mode))
			handle_is_directory(command, cmd_info, env_list, path_sp_w_slash);
		handle_command_found(cmd_info, env_list, path_sp_w_slash);
	}
	path_val = get_env_value(env_list, "PATH");
	if (!path_val || path_val[0] == '\0')
		handle_is_directory_empty(command, cmd_info, env_list, path_sp_w_slash);
	else
		handle_command_not_found(command, cmd_info, env_list, path_sp_w_slash);
	close_fd(cmd_info);
}

char	*find_builtin_or_exit(char **path_sp_w_slash, t_command *cmd_inf, \
		t_env *env_list)
{
	char	*built_in_path;

	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf->tokens);
	if (!built_in_path)
		exec_builtin_or_exit(cmd_inf->tokens[0], \
		cmd_inf, env_list, path_sp_w_slash);
	return (built_in_path);
}
