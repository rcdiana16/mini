/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:11:15 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/27 15:17:23 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_token_count(t_command *cmd_info)
{
	int	count;

	count = 0;
	while (cmd_info->tokens[count])
		count++;
	return (count);
}

bool	has_enclosed_single_quotes(char *token)
{
	int	len;

	if (token == NULL || ft_strlen(token) < 2)
		return (false);
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (true);
	return (false);
}

void	clean_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (ft_strlen(token) == 2)
		return ;
	while (token[j])
	{
		if (token[j] != '\"')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}

void	remove_single_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (ft_strlen(token) == 2)
		return ;
	while (token[j])
	{
		if (token[j] != '\'')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}

void	delete_quotes(char *token)
{
	remove_single_quotes(token);
	clean_quotes(token);
}
