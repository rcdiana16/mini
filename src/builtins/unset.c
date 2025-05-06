/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:58 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 14:43:07 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	remove_first_node(t_env *env_mini, char *var)
{
	t_env	*tmp;

	if (!var)
		return (0);
	if (env_mini && ft_strncmp((env_mini)->variable, var, \
		ft_strlen(var)) == 0 && ft_strlen(var) != 0)
	{
		tmp = env_mini;
		env_mini = tmp->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	remove_variable(t_env *env_mini, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	if (!var)
		return ;
	tmp = env_mini;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0 \
			&& ft_strlen(var) != 0)
		{
			prev->next = tmp->next;
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env *env_mini, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd || !cmd[1])
		return ;
	while (cmd[i])
	{
		if (remove_first_node(env_mini, cmd[i]))
			return ;
		remove_variable(env_mini, cmd[i]);
		i++;
	}
}
