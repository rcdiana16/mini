/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_sp_ch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:28:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/16 00:48:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_skip_next(int *skip_next, int *i)
{
	*skip_next = 0;
	(*i)++;
}

void	handle_special_char(char *cmd, t_command *cmd_info, int *i, int *j)
{
	char	quote;

	quote = cmd[*i];
	if (cmd[*i + 1] == quote)
	{
		(*i)++;
		return ;
	}
	cmd[*j] = cmd[*i];
	(*j)++;
	if (quote == '\'')
		cmd_info->quotes_s++;
	else if (quote == '\"')
		cmd_info->quotes_d++;
}

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;
	int	j;
	int	skip_next;

	i = 0;
	j = 0;
	skip_next = 0;
	while (cmd[i])
	{
		if (skip_next)
		{
			handle_skip_next(&skip_next, &i);
			continue ;
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
			handle_special_char(cmd, cmd_info, &i, &j);
		else
		{
			cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	cmd[j] = '\0';
}
