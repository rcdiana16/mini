/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 10:24:33 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
/*
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
}*/

static char	**append_rest_tokens(char **tokens, char **rest_tokens)
{
	char	**new_tokens;
	int		t_len;
	int		r_len;
	int		i;
	int		j;

	t_len = ft_arrlen(tokens);
	r_len = ft_arrlen(rest_tokens);
	new_tokens = malloc(sizeof(char *) * (t_len + r_len + 1));
	if (!new_tokens)
		return (NULL);
	i = -1;
	while (++i < t_len)
		new_tokens[i] = tokens[i];
	j = -1;
	while (++j < r_len)
		new_tokens[i + j] = rest_tokens[j];
	new_tokens[i + j] = NULL;
	free(tokens);
	return (new_tokens);
}

/*
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
}*/
static char	**handle_multiple_equals(char *cmd)
{
	char	*first_equal;
	char	*rest;
	char	**tokens;
	char	**rest_tokens;
	char	**combined_tokens;

	first_equal = ft_strchr(cmd, '=');
	*first_equal = '\0';
	rest = first_equal + 1;
	tokens = ft_split(cmd, ' ');
	rest_tokens = ft_split(rest, ' ');
	combined_tokens = append_rest_tokens(tokens, rest_tokens);
	free(rest_tokens);
	return (combined_tokens);
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
