/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:08 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 15:50:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash)
{
	int	exit_builtin;

	exit_builtin = check_builtins(cmd_info->tokens, env_list, \
		cmd_info, path_sp_w_slash);
	if (exit_builtin != -1)
	{
		restore_heredoc_stdin(cmd_info);
		return (exit_builtin);
	}
	return (-1);
}

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	*allocate_env_entry(const char *variable, const char *value)
{
	size_t	var_len;
	size_t	val_len;
	size_t	total_len;
	char	*entry;

	var_len = ft_strlen(variable);
	val_len = ft_strlen(value);
	total_len = var_len + val_len + 2;
	entry = malloc(total_len);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, variable, var_len + 1);
	entry[var_len] = '=';
	ft_strlcpy(entry + var_len + 1, value, val_len + 1);
	return (entry);
}

char	**allocate_env_array(int size)
{
	char	**env_array;

	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	return (env_array);
}

char	**convert_env_to_array(t_env *env_mini)
{
	int		size;
	char	**env_array;
	int		i;

	size = env_list_size(env_mini);
	env_array = allocate_env_array(size);
	if (!env_array)
		return (NULL);
	i = 0;
	while (env_mini)
	{
		env_array[i] = allocate_env_entry(env_mini->variable, env_mini->value);
		if (!env_array[i])
		{
			while (i-- > 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env_mini = env_mini->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
