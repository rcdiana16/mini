/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd_split.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:21:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/07 19:22:38 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_normal_token(char **tokens, char **new_tokens, int *i, int *j)
{
	new_tokens[(*j)++] = ft_strdup(tokens[*i]);
}

static int	is_special_case(char *token)
{
	if (ft_strncmp(token, "><", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<>", 2) == 0)
		return (1);
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

static int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static int	should_split_at(char *token, int i)
{
	if (!is_operator_char(token[i]))
		return (0);
	if (token[i] == '|')
		return (1);
	if (i == 0)
		return (0);
	if ((token[i] == '>' && token[i + 1] == '>') || \
		(token[i] == '<' && token[i + 1] == '<'))
		return (0);
	if (i > 0 && ((token[i - 1] == '>' && token[i] == '>') || \
			(token[i - 1] == '<' && token[i] == '<')))
		return (0);
	return (1);
}

static int	count_tokens_after_split(char *token)
{
	int		i;
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	count = 1;
	in_single_quote = false;
	in_double_quote = false;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && should_split_at(token, i))
			count += 2;
		i++;
	}
	return (count);
}

static void	split_token_at_operator(char *token, char ***result, \
			int *result_index)
{
	int		i;
	int		start;
	bool	in_single_quote;
	bool	in_double_quote;
	char	*part;

	i = 0;
	start = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && should_split_at(token, i))
		{
			if (i > start)
			{
				part = ft_substr(token, start, i - start);
				(*result)[(*result_index)++] = part;
			}
			if (token[i] == '>' && token[i + 1] == '>')
			{
				(*result)[(*result_index)++] = ft_strdup(">>");
				i++;
			}
			else if (token[i] == '<' && token[i + 1] == '<')
			{
				(*result)[(*result_index)++] = ft_strdup("<<");
				i++;
			}
			else
			{
				part = ft_substr(token, i, 1);
				(*result)[(*result_index)++] = part;
			}
			start = i + 1;
		}
		i++;
	}
	if (token[start])
		(*result)[(*result_index)++] = ft_strdup(token + start);
}

char	**split_tokens_with_operators(char **tokens)
{
	int		i;
	int		j;
	int		total_tokens;
	char	**result;
	bool	has_embedded_operators;
	int		token_count;

	i = 0;
	total_tokens = 0;
	has_embedded_operators = false;
	while (tokens[i])
	{
		token_count = count_tokens_after_split(tokens[i]);
		total_tokens += token_count;
		if (token_count > 1)
			has_embedded_operators = true;
		i++;
	}
	if (!has_embedded_operators)
		return (tokens);
	result = calloc(total_tokens + 1, sizeof(char *));
	if (!result)
		return (tokens);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (count_tokens_after_split(tokens[i]) > 1)
			split_token_at_operator(tokens[i], &result, &j);
		else
			result[j++] = ft_strdup(tokens[i]);
		i++;
	}
	result[j] = NULL;
	free_arr(tokens);
	return (result);
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
