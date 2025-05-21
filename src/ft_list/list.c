/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:08:20 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/21 02:23:24 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*DIANA I moved to file lis_node.c
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
}*/
/* MAXIME moved to the list_node.c file
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
}*/

static int	calculate_shlvl(const char *shlvl_str)
{
	int	shlvl;

	if (!shlvl_str || !*shlvl_str)
		return (1);
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		return (0);
	if (shlvl >= 999)
	{
		write(2, "warning: shell level (", 21);
		ft_putnbr_fd(shlvl + 1, 2);
		write(2, ") too high, resetting to 1\n", 26);
		return (1);
	}
	return (shlvl + 1);
}

static void	handle_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env_list, "SHLVL");
	shlvl = calculate_shlvl(shlvl_str);
	new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
	{
		update_or_append_node(env_list, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

/*DIANA i cut it are the two previous functions
static void	handle_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env_list, "SHLVL");
	if (!shlvl_str || !*shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		else if (shlvl >= 999)
		{
			write(2, "warning: shell level (", 21);
			ft_putnbr_fd(shlvl + 1, 2);
			write(2, ") too high, resetting to 1\n", 26);
			shlvl = 1;
		}
		else
			shlvl++;
	}
	new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
	{
		update_or_append_node(env_list, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}*/

static void	init_default_env(t_env **env_list)
{
	char	cwd[PATH_MAX];
	char	*ret;

	ret = getcwd(cwd, sizeof(cwd));
	if (ret != NULL)
		append_node(env_list, "PWD", cwd);
	handle_shlvl(env_list);
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
	handle_shlvl(&env_list);
	return (env_list);
}

t_env	*initialize_environment(char **env, t_env *env_list)
{
	return (get_list_env(env, env_list));
}
