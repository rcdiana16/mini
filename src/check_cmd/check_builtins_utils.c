/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:41 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 17:52:02 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
	char **path)
{
	int	exit;

	exit = 0;
	if (!cmd)
		return (0);
	exit = check_standard_builtins(cmd, env_mini, &cmd_info, path);
	if (exit != -1)
		return (exit);
	exit = check_env_builtins(cmd, env_mini);
	if (exit != -1)
		return (exit);
	return (-1);
}
