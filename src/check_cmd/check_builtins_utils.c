/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:41 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 00:04:04 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_variable_assignment(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=');
}

static int	handle_variable_assignment(t_env *env_mini, char *cmd)
{
	char	**tokens;
	int		ret;

	tokens = get_tokens(cmd);
	if (!tokens)
		return (1);
	ret = handle_export_arg(env_mini, cmd);
	free_arr(tokens);
	return (ret);
}

int	check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
		char **path)
{
	int	exit;

	exit = 0;
	if (!cmd)
		return (0);
	if (cmd[0] && is_variable_assignment(cmd[0]))
		return (handle_variable_assignment(env_mini, cmd[0]));
	exit = check_standard_builtins(cmd, env_mini, &cmd_info, path);
	if (exit != -1)
		return (exit);
	exit = check_env_builtins(cmd, env_mini);
	if (exit != -1)
		return (exit);
	return (-1);
}
