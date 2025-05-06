/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:04:14 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 16:07:18 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_command_not_found(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}
