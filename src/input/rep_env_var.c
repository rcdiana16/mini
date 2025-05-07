/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:46 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 11:35:45 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_var_name_length(t_cmd_state *state)
{
	int	length;

	length = 0;
	while (state->cmd[state->i] && (ft_isalnum(state->cmd[state->i]) \
			|| state->cmd[state->i] == '_'))
	{
		length++;
		(state->i)++;
	}
	return (length);
}

static char	*copy_var_name(t_cmd_state *state, int start, int length)
{
	int		j;
	char	*var_name;

	var_name = malloc(sizeof(char) * (length + 1));
	if (!var_name)
		return (NULL);
	j = 0;
	while (j < length)
	{
		var_name[j] = state->cmd[start + j];
		j++;
	}
	var_name[length] = '\0';
	return (var_name);
}

char	*extract_var_name(t_cmd_state *state)
{
	int	start;
	int	length;

	start = state->i;
	length = get_var_name_length(state);
	if (length == 0)
		return (NULL);
	return (copy_var_name(state, start, length));
}

int	process_env_var(t_cmd_state *state, char *result, int j, t_env *env_mini)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = extract_var_name(state);
	if (var_name)
	{
		var_value = get_env_value(env_mini, var_name);
		if (!var_value)
			var_value = "";
		tmp = var_value;
		while (*tmp)
			result[j++] = *tmp++;
		free(var_name);
	}
	return (j);
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
