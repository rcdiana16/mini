/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd_split.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:21:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 23:14:54 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_normal_token(char **tokens, char **new_tokens, int *i, int *j)
{
	new_tokens[(*j)++] = ft_strdup(tokens[*i]);
}
/*
char	**split_joined_redirections(char **tokens)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = 0;
	j = 0;
	new_tokens = allocate_new_tokens(tokens);
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		if ((ft_strncmp(tokens[i], "><", 2) == 0 || \
		(tokens[i], "<>", 2) == 0 *//*|| \
	(ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) > 1)*//*))
			copy_normal_token(tokens, new_tokens, &i, &j);
		if ((ft_strncmp(tokens[i], ">>", 2) == 0 && ft_strlen(tokens[i]) > 2) \
		|| (ft_strncmp(tokens[i], "<<", 2) == 0 && ft_strlen(tokens[i]) > 2))
			split_double_redirection(tokens, new_tokens, &i, &j);
		else if ((tokens[i][0] == '>' || tokens[i][0] == '<') && \
			ft_strlen(tokens[i]) > 1 && \
			((tokens[i][1] != '>' && tokens[i][1] != '<') || tokens[i][2] == \
			'\0') && !ft_strchr(tokens[i] + 1, '>') && \
			!ft_strchr(tokens[i] + 1, '<'))
			split_single_redirection(tokens, new_tokens, &i, &j);
		else
			copy_normal_token(tokens, new_tokens, &i, &j);
		i++;
	}
	new_tokens[j] = NULL;
	free_arr(tokens);
	return (new_tokens);
}*/

static int	is_special_case(char *token)
{
	if (ft_strncmp(token, "><", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<>", 2) == 0)
		return (1);
	// if (ft_strchr(token, '|') && ft_strlen(token) > 1)
	return (0);
}

static int	is_double_redirect(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) > 2)
		return (1);
	if (ft_strncmp(token, "<<", 2) == 0 && ft_strlen(token) > 2)
		return (1);
	return (0);
}

static int	is_single_redirect(char *token)
{
	if ((token[0] == '>' || token[0] == '<') && ft_strlen(token) > 1 && \
	(token[1] != '>' && token[1] != '<'))
	{
		if (!ft_strchr(token + 1, '>') && !ft_strchr(token + 1, '<'))
			return (1);
	}
	return (0);
}

char	**split_joined_redirections(char **tokens)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = 0;
	j = 0;
	new_tokens = allocate_new_tokens(tokens);
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		if (is_special_case(tokens[i]))
			copy_normal_token(tokens, new_tokens, &i, &j);
		else if (is_double_redirect(tokens[i]))
			split_double_redirection(tokens, new_tokens, &i, &j);
		else if (is_single_redirect(tokens[i]))
			split_single_redirection(tokens, new_tokens, &i, &j);
		else
			copy_normal_token(tokens, new_tokens, &i, &j);
		i++;
	}
	new_tokens[j] = NULL;
	free_arr(tokens);
	return (new_tokens);
}
