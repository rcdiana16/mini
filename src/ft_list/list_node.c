/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:33:32 by diana             #+#    #+#             */
/*   Updated: 2025/05/21 02:17:58 by diana            ###   ########.fr       */
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

void	update_or_append_node(t_env **env_list, const char *key, char *value)
{
	t_env	*node;

	node = *env_list;
	while (node)
	{
		if (ft_strncmp(node->variable, key, ft_strlen(node->value) + 1) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
	append_node(env_list, "SHLVL", value);
}
