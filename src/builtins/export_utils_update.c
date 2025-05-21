/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:13:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/21 01:23:55 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_existing_variable(t_env *env_mini, char **tokens)
{
	char	*value;
	char	*old_value;

	value = NULL;
	old_value = NULL;
	if (!env_mini)
		return (0);
	if (!tokens[1])
		return (1);
	value = ft_strdup(tokens[1]);
	if (!value)
		return (0);
	old_value = value;
	join_cmd_values(tokens, &value);
	delete_quotes(value);
	if (value != old_value)
		free (old_value);
	free (env_mini->value);
	env_mini->value = value;
	return (1);
}

int	update_existing_variable(t_env *env_mini, char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (!env_mini)
		return (0);
	while (env_mini)
	{
		if (ft_strncmp(tokens[0], env_mini->variable, \
			ft_strlen(tokens[0]) + 1) == 0)
			return (handle_existing_variable(env_mini, tokens));
		env_mini = env_mini->next;
	}
	return (0);
}

int	alloc_and_init_new_var(t_env *env_mini, char **tokens)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (1);
	init_new_variable(new_var, tokens);
	if (env_mini)
		add_new_variable(env_mini, tokens, new_var);
	else
	{
		free(new_var->variable);
		free(new_var->value);
		free(new_var);
		return (1);
	}
	return (0);
}

int	handle_export_arg(t_env *env_mini, char *arg)
{
	char	**tokens;
	int		err;

	if (is_invalid_identifier(arg))
		return (1);
	tokens = get_tokens(arg);
	err = 0;
	if (!env_mini || !update_existing_variable(env_mini, tokens))
		err = alloc_and_init_new_var(env_mini, tokens);
	free_arr(tokens);
	return (err);
}
