/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:21:28 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/27 22:30:47 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*make_good_cmd(char *cmd)
{
	char	*tmp;

	remove_single_quotes(cmd);
	tmp = realloc(cmd, ft_strlen(cmd) + 1);
	if (!tmp)
	{
		perror("realloc failed");
		return (cmd);
	}
	return (tmp);
}
/*
char	*make_good_cmd(char *cmd)
{
	size_t new_len;
	char *tmp;

	// Safely shrink the string in-place
	remove_single_quotes(cmd);

	new_len = ft_strlen(cmd) + 1;
	tmp = realloc(cmd, new_len); // shrink buffer *after* shortening
	if (!tmp)
	{
		perror("realloc failed");
		return cmd; // still valid, since realloc failed
	}
	return tmp;
}
*/

char	*make_good_cmd2(char *cmd)
{
	char	*tmp;

	clean_quotes(cmd);
	tmp = realloc(cmd, ft_strlen(cmd) + 1);
	if (!tmp)
	{
		perror("realloc failed");
		return (cmd);
	}
	return (tmp);
}

void	remove_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

bool	has_enclosed_double_quotes(char *token)
{
	int	len;

	if (token == NULL || ft_strlen(token) < 2)
		return (false);
	len = ft_strlen(token);
	if (token[0] == '\"' && token[len - 1] == '\"')
		return (true);
	return (false);
}

int	copy_non_var_part(t_cmd_state *state, char *result, int j)
{
	result[j++] = state->cmd[state->i];
	(state->i)++;
	return (j);
}
