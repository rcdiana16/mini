/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:24:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/23 17:09:42 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(t_command *cmd_info)
{
	int	i;

	if (!cmd_info)
		return ;
	if (cmd_info->tokens)
	{
		i = 0;
		while (cmd_info->tokens[i])
		{
			free(cmd_info->tokens[i]);
			i++;
		}
		free(cmd_info->tokens);
	}
	if (cmd_info->envp)
		free_arr(cmd_info->envp);
	if (cmd_info->file_out)
		free(cmd_info->file_out);
	if (cmd_info->file_in)
		free(cmd_info->file_in);
	free(cmd_info);
}

void	free_node(t_env *node)
{
	if (!node)
		return ;
	free(node->variable);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free_node(tmp);
	}
}

void	free_split_data(t_split_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->res)
	{
		i = 0;
		while (data->res[i])
		{
			free(data->res[i]);
			i++;
		}
		free(data->res);
	}
	if (data->j)
		free(data->j);
	if (data->s_word)
		free(data->s_word);
	free(data);
}

void	free_cmd_state(t_cmd_state *state)
{
	if (!state)
		return ;
	if (state->cmd)
		free(state->cmd);
	free(state);
}
