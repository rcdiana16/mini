/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace_tok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:08:40 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/28 11:11:04 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_token_with_empty(t_command *cmd_info, int i)
{
	free(cmd_info->tokens[i]);
	cmd_info->tokens[i] = ft_strdup("");
}

void	replace_token_with_tmp(t_command *cmd_info, int i, char *tmp)
{
	free(cmd_info->tokens[i]);
	cmd_info->tokens[i] = tmp;
}

void	remove_token(t_command *cmd_info, int i, char *tmp)
{
	int	j;

	free(cmd_info->tokens[i]);
	free(tmp);
	j = i;
	while (cmd_info->tokens[j])
	{
		cmd_info->tokens[j] = cmd_info->tokens[j + 1];
		j++;
	}
	cmd_info->tokens[j] = NULL;
}
