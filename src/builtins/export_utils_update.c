/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:13:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/18 10:18:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_existing_variable(t_env *env_mini, char **tokens)
{
	char	*value;
	char	*old_value;

	free(env_mini->value);
	if (tokens[1])
		value = ft_strdup(tokens[1]);
	else
		value = ft_strdup("");
	old_value = value;
	join_cmd_values(tokens, &value);
	delete_quotes(value);
	if (value != old_value)
		free(old_value);
	env_mini->value = value;
	return (1);
}

int	update_existing_variable(t_env *env_mini, char **tokens)
{
	if (!tokens || !tokens[0])
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
