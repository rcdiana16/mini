/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:22:54 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 16:15:25 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_special_var(t_cmd_state *state, char *result, \
	int j, t_shell *shell)
{
	j = process_exit_code(result, j, shell);
	state->i++;
	return (j);
}

static int	process_env_var_internal(t_cmd_state *state, char *result, \
	int j, t_env *env_mini)
{
	return (process_env_var(state, result, j, env_mini));
}

int	process_var(t_cmd_state *state, char *result, int j, t_shell_env *shell_env)
{
	state->i++;
	if (state->cmd[state->i] == '?')
		return (handle_special_var(state, result, j, shell_env->shell));
	return (process_env_var_internal(state, result, j, shell_env->env_mini));
}

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
		if (state->cmd[state->i] == '$' && state->cmd[state->i + 1] \
		&& state->cmd[state->i + 1] != ' ' && state->cmd[state->i + 1] != '$')
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
