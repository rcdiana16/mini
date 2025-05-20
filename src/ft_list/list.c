/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:08:20 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/20 17:33:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_node(char *var, char *val)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_strdup(var);
	if (!new_node->variable)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(val);
	if (!new_node->value)
	{
		free(new_node->variable);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_env **head, char *var, char *val)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_node(var, val);
	if (!new_node)
	{
		write(2, "Error: Failed to create node\n", \
		ft_strlen("Error: Failed to create node\n"));
		return ;
	}
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

static void	init_default_env(t_env **env_list)
{
	char	cwd[PATH_MAX];
	char	*ret;

	ret = getcwd(cwd, sizeof(cwd));
	if (ret != NULL)
		append_node(env_list, "PWD", cwd);
	append_node(env_list, "SHLVL", "1");
	append_node(env_list, "_", "./minishell");
}

t_env	*get_list_env(char **envp, t_env *env_list)
{
	int		i;
	char	*equal_sign;

	env_list = NULL;
	if (!envp || !envp[0])
	{
		init_default_env(&env_list);
		return (env_list);
	}
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			append_node(&env_list, envp[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	return (env_list);
}

t_env	*initialize_environment(char **env, t_env *env_list)
{
	return (get_list_env(env, env_list));
}
