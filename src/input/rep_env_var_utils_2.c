/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:21:16 by diana             #+#    #+#             */
/*   Updated: 2025/04/23 17:28:52 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*initialize_replace_env_vars(t_cmd_state *state)
{
	char	*result;

	result = malloc(256);
	if (!result)
		return (NULL);
	state->i = 0;
	return (result);
}

char	*process_replace_env_vars(t_cmd_state *state, \
	char *result, t_shell_env *shell_env)
{
	int	j;

	j = 0;
	while (state->cmd[state->i])
	{
		if (state->cmd[state->i] == '$' && state->cmd[state->i + 1])
			j = process_var(state, result, j, shell_env);
		else
			j = copy_non_var_part(state, result, j);
	}
	result[j] = '\0';
	if (j == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	*replace_env_vars(char *cmd, t_env *env_mini, t_shell *shell)
{
	t_cmd_state	state;
	t_shell_env	shell_env;
	char		*result;

	state.cmd = cmd;
	state.i = 0;
	state.cmd_info = NULL;
	shell_env.env_mini = env_mini;
	shell_env.shell = shell;
	result = initialize_replace_env_vars(&state);
	if (!result)
		return (NULL);
	return (process_replace_env_vars(&state, result, &shell_env));
}
