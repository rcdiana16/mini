/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 17:35:02 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
char	**get_tokens(char *cmd)
{
	char	**tokens;
	int		equal_count = 0;
	char	*ptr = cmd;
	char	*first_equal;

	while (*ptr)
	{
		if (*ptr == '=')
			equal_count++;
		ptr++;
	}
	if (equal_count == 1)
	{
		tokens = ft_split(cmd, '=');
	}
	else if (equal_count > 1)
	{
		first_equal = strchr(cmd, '=');
		*first_equal = '\0';
		tokens = ft_split(cmd, ' ');
		char	*rest = first_equal + 1;
		char	**rest_tokens = ft_split(rest, ' ');
		int i = 0, j = 0;
		while (tokens[i]) i++;
		while (rest_tokens[j])
		{
			tokens[i] = rest_tokens[j];
			i++;
			j++;
		}
		tokens[i] = NULL;
		free(rest_tokens);
	}
	else
		tokens = ft_split(cmd, ' ');
	return (tokens);
}
*/

static int	count_equals(char *cmd)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			count++;
		i++;
	}
	return (count);
}

static char	**handle_single_equal(char *cmd)
{
	return (ft_split(cmd, '='));
}

static void	append_rest_tokens(char **tokens, char **rest_tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
		i++;
	j = 0;
	while (rest_tokens[j])
	{
		tokens[i] = rest_tokens[j];
		i++;
		j++;
	}
	tokens[i] = NULL;
}

static char	**handle_multiple_equals(char *cmd)
{
	char	*first_equal;
	char	*rest;
	char	**tokens;
	char	**rest_tokens;

	first_equal = ft_strchr(cmd, '=');
	*first_equal = '\0';
	rest = first_equal + 1;
	tokens = ft_split(cmd, ' ');
	rest_tokens = ft_split(rest, ' ');
	append_rest_tokens(tokens, rest_tokens);
	free(rest_tokens);
	return (tokens);
}

char	**get_tokens(char *cmd)
{
	char	**tokens;
	int		equal_count;

	equal_count = count_equals(cmd);
	if (equal_count == 1)
		tokens = handle_single_equal(cmd);
	else if (equal_count > 1)
		tokens = handle_multiple_equals(cmd);
	else
		tokens = ft_split(cmd, ' ');
	return (tokens);
}
